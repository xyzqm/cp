#define LCA
#include "graph.h"

const int N = 2e5 + 1;

int main() {
  int n, q; cin >> n >> q;
  Tree<N> t(n);
  t.input().root(1).dfs();
  while (q--) {
    int u, v; cin >> u >> v;
    cout << t.D(u, v) << endl;
  }
}
