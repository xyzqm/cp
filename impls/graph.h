#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include "sgt.h"
#include "util.h"
using namespace std;

struct W { // weighted edge
  int v; ll w;
  friend istream& operator>>(istream& is, W e) { return is >> e.v >> e.w; }
  bool operator==(const W o) const { return make_pair(v, w) == make_pair(o.v, o.w); }
  operator int() const { return v; }
};

template <typename T, class V = vector<T>>
struct Graph {
  int n, m;
  Graph(int n, int m) : n(n), m(m) {}
  V g[N];
  void add(int u, T e) { ::add(g[u], e); }
  void u(int u, int v);
  // undirected input
  Graph& input() {
    for (int i = 0; i < m; i++) {
      int u; T v; cin >> u >> v;
      ::add(g[u], v);
      if constexpr (is_same_v<T, W>) ::add(g[v], W{u, v.w});
      else ::add(g[v], u);
    }
    return *this;
  }
};

template <>
void Graph<int>::u(int u, int v) {
  add(u, v);
  add(v, u);
}

template <typename T, typename V = vector<T>>
struct Tree : Graph<T, V> {
  int r, s[N], p[N], d[N]{};
  Tree(int n) : Graph<T, V>(n, n - 1) {
    fill(s, s + n + 1, 1); // TODO: allow initializing weighted nodes later
  }
  Tree& root(int x) { return r = p[x] = x, *this; }
  int dfs(int x) {
    for (T e : this->g[x]) if (e != p[x]) {
      int w = 1;
      if constexpr (is_same_v<T, W>) w = e.w;
      d[e] = d[p[e] = x] + w;
      s[x] += dfs(e);
    }
    return s[x];
  }
  Tree& dfs() { return dfs(r), *this; }
  Tree& input() { return Graph<T, V>::input(), *this; }
};
