// https://judge.yosupo.jp/problem/point_add_range_sum
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
using ll = long long;
const int N = 5e5 + 1;
#define COMB(a, b) (a) + (b)
int n;
ll a[4 * N];
struct SGT {
  ll a[4 * N];
  ll query(int i, int j, int p = 1, int l = 0, int r = n) {
      if (r <= i || l >= j) return 0;
      else if (i <= l && r <= j) return a[p];
      else {
        int m = (l + r) / 2;
        return COMB(query(i, j, 2 * p, l, m), query(i, j, 2 * p + 1, m, r));
      }
  }
  void upd(int i, int x, int p = 1, int l = 0, int r = n) {
      if (r - l == 1) a[p] += x;
      else {
          int m = (l + r) / 2;
          if (i < m) upd(i, x, 2 * p, l, m);
          else upd(i, x, 2 * p + 1, m, r);
          a[p] = COMB(a[2 * p], a[2 * p + 1]);
      }
  }
  void build(ll* l, ll* r, int p = 1) {
    if (r - l == 1) a[p] = *l;
    else if (r - l > 1) {
        ll* m = l + (r - l) / 2;
        build(l, m, 2 * p);
        build(m, r, 2 * p + 1);
        a[p] = COMB(a[2 * p], a[2 * p + 1]);
    }
  }
} sgt;
int main() {
    int q; cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    sgt.build(a, a + n);
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        if (!x) sgt.upd(y, z);
        else cout << sgt.query(y, z) << endl;
    }
}
