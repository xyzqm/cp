#define LCA
#define CENTROID
#include "graph.h"
using P = pair<int, int>;
const int N = 1e5 + 1;

int red[N];

int main() {
  fill(red, red + N, 1e9);
  int n, q; cin >> n >> q;
  Tree<N> t(n);
  t.input().root(1).dfs().decompose();
  assert(!t.cp[t.cr]);
  auto upd = [&](int x) {
    int c = 0;
    int y = x;
    while (y) {
      /* if (n > 1000) cout << y << " " << t.cp[y] << endl; */
      red[y] = min(red[y], t.D(y, x));
      y = t.cp[y];
    }
    assert(c < 20);
  };
  auto query = [&](int x) {
    int c = 0;
    int y = x, r = 1e9;
    while (y) {
      /* if (n > 1000) cout << y << " " << t.cp[y] << endl; */
      r = min(r, red[y] + t.D(x, y));
      y = t.cp[y];
      ++c;
    }
    assert(c < 20);
    return r;
  };
  upd(1);
  while (q--) {
    int t, x; cin >> t >> x;
    if (t == 1) upd(x);
    else cout << query(x) << '\n';
  }
}
