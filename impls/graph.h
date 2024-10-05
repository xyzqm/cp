#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include "sgt.h"
using namespace std;

struct W { // weighted edge
  int v; ll w;
  friend istream& operator>>(istream& is, W e) { return is >> e.v >> e.w; }
};

template <typename T>
struct Graph {
  int n, m;
  Graph(int n, int m) : n(n), m(m) {}
  vector<T> g[N];
  void add_edge(int u, T e) { g[u].push_back(e); }
  void undirected(int u, int v);
  Graph& input() {
    for (int i = 0; i < m; i++) {
      int u; T v; cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    return *this;
  }
};

template<>
void Graph<int>::undirected(int u, int v) {
  g[u].push_back(v);
  g[v].push_back(u);
}

struct Tree : Graph<int> {
  int r, s[N], p[N], d[N]{};
  Tree(int n) : Graph<int>(n, n - 1) {
    fill(s, s + n + 1, 1); // TODO: allow initializing weighted nodes later
  }
  Tree& root(int x) { return r = p[x] = x, *this; }
  int dfs(int x) {
    for (int y : g[x]) {
      d[y] = d[p[y] = x] + 1;
      g[y].erase(find(g[y].begin(), g[y].end(), x));
      s[x] += dfs(y);
    }
    return s[x];
  }
  Tree& dfs() { return dfs(r), *this; }
  Tree& input() { return Graph<int>::input(), *this; }
};

