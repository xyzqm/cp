// https://judge.yosupo.jp/problem/point_add_range_sum
#include <cassert>
#include <functional>
#include "constants.h"
using namespace std;
template <int N, typename T = int>
// 0-indexed segment tree
struct SGT {
  T a[2 * N], t0;
  function<T(T, T)> f;
  bool s;
  SGT& fn(function<T(T, T)> f, bool s, T x) { return this->f = f, this->s = s, t0 = x, *this; }
  SGT& fill(T x) { return ::fill(a, a + 2 * N, x), *this; }
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
    i += N;
    for (a[i] = s ? x : f(x, a[i]); i >>= 1; ) a[i] = f(a[i << 1], a[i << 1|1]);
  }
};
