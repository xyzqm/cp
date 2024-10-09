// https://judge.yosupo.jp/problem/point_add_range_sum
#include <cassert>
#include <functional>
#include "constants.h"
using namespace std;
template <int N, typename T>
// 0-indexed segment tree
struct SGT {
  T a[2 * N], t0;
  function<T(T, T)> f;
  SGT& fn(function<T(T, T)> f, T x) { return this->f = f, t0 = x, *this; }
  // query on range [l, r)
  T query(int l, int r) {
    T tl = t0, tr = t0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
      if (l & 1) tl = f(tl, a[l++]);
      if (r & 1) tr = f(a[--r], tr);
    }
    return f(tl, tr);
  }
  void upd(int i, T x) {
    for (a[i += N] = x; i >>= 1; ) a[i] = f(a[i << 1], a[i << 1|1]);
  }
  void build(T* l, T* r, int p) {
    if (r - l == 1) a[p] = *l;
    else if (r - l > 1) {
      T* m = l + (r - l) / 2;
      build(l, m, 2 * p);
      build(m, r, 2 * p + 1);
      a[p] = f(a[2 * p], a[2 * p + 1]);
    }
  }
  void build (T* a) { build(a, a + N, 1); }
};
