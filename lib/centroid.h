#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include "graph.h"
using namespace std;
using P = pair<int, int>;

template <int N, typename T>
struct Centroid {
  Tree<N, T, set<T>> &t;
  int r;
  vector<int> g[N];
  int decompose(int x, int n) {
    for (auto y : t.g[x]) {
      if (t.sz[y] > n / 2) return decompose(y, x, n);
    }
    for(int y : t.g[x]) {
      t.g[y].erase(x);
      g[x].push_back(decompose(y, x, t.sz[y]));
    }
    t.g[x].clear();
    return x;
  }
  Centroid& decompose() {
    return r = decompose(t.r, t.sz[t.r]), *this;
  }
};

