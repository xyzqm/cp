#define LCA
#define CENTROID
#include "graph.h"
using P = pair<int, int>;
const int N = 1e5 + 1;

ll red[N];
Tree<N> t;
void upd(int x) {
  int y = x;
  while (y) {
    red[y] = min(red[y], t.D(y, x));
    y = t.cp[y];
  }
};
int query(int x) {
  int y = x, r = 1e9;
  while (y) {
    r = min(r, red[y] + t.D(x, y));
    y = t.cp[y];
  }
  return r;
};

int main() {
  fill(red, red + N, 1e9);
  int n, q; cin >> n >> q;
  t.init(n).input().root(1).dfs().decompose();
  upd(1);
  while (q--) {
    int t, x; cin >> t >> x;
    if (t == 1) upd(x);
    else cout << query(x) << '\n';
  }
}
