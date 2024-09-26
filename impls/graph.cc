#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include "sgt.cc"

struct W { // weighted edge
  int v; ll w;
  friend istream& operator>>(istream& is, W e) { return is >> e.v >> e.w; }
};

template <typename T>
struct Graph {
  int n, m;
  Graph(int n, int m) : n(n), m(m) {}
  vector<T> g[N];
  Graph& input() {
    for (int i = 0; i < m; i++) {
      int u; T v; cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    return *this;
  }
};

template <typename T>
struct Tree : Graph<T> {
  int r, s[N], p[N], d[N]{};
  Tree(int n) : Graph<T>(n, n - 1) {
    fill(s, s + n + 1, 1); // TODO: allow initializing weighted nodes later
  }
  Tree& root(int x) { return r = x, *this; }
  vector<int>& ex(int x);
  int dfs(int x) {
    for (int y : ex(x)) {
      d[y] = d[p[y] = x] + 1;
      ex(y).erase(find(ex(y).begin(), ex(y).end(), x));
      s[x] += dfs(y);
    }
    return s[x];
  }
  Tree& dfs() { return dfs(r), *this; }
  Tree& input() { return Graph<T>::input(), *this; }
};
template <> vector<int>& Tree<int>::ex(int x) { return g[x]; }

