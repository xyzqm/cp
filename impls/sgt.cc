// https://judge.yosupo.jp/problem/point_add_range_sum
#include <iostream>
#include <cassert>
#include <functional>
using namespace std;
using ll = long long;
const int N = 5e5 + 1;
ll a[N];
template <typename T>
struct SGT {
  T a[4 * N];
  function<T(T, T)> f;
  SGT& fn(function<T(T, T)> f) { return this->f = f, *this; }
  ll query(int i, int j, int p = 1, int l = 0, int r = N) {
    if (r <= i || l >= j) return 0;
    else if (i <= l && r <= j) return a[p];
    else {
      int m = (l + r) / 2;
      return f(query(i, j, 2 * p, l, m), query(i, j, 2 * p + 1, m, r));
    }
  }
  void upd(int i, T x, int p = 1, int l = 0, int r = N) {
    if (r - l == 1) a[p] += x;
    else {
      int m = (l + r) / 2;
      if (i < m) upd(i, x, 2 * p, l, m);
      else upd(i, x, 2 * p + 1, m, r);
      a[p] = f(a[2 * p], a[2 * p + 1]);
    }
  }
  void build(T* l, T* r, int p) {
    if (r - l == 1) a[p] = *l;
    else if (r - l > 1) {
      ll* m = l + (r - l) / 2;
      build(l, m, 2 * p);
      build(m, r, 2 * p + 1);
      a[p] = f(a[2 * p], a[2 * p + 1]);
    }
  }
  void build (T* a) { build(a, a + N, 1); }
};

/* int main() { */
/*   SGT<ll> sgt; */
/*   int n, q; cin >> n >> q; */
/*   for (int i = 0; i < n; i++) cin >> a[i]; */
/*   sgt.fn([](ll x, ll y) { return x + y; }).build(a); */
/*   while (q--) { */
/*       int x, y, z; */
/*       cin >> x >> y >> z; */
/*       if (!x) sgt.upd(y, z); */
/*       else cout << sgt.query(y, z) << endl; */
/*   } */
/* } */

