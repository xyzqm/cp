// https://www.acmicpc.net/problem/20603
#include "hld.h"
#include <array>
#include <climits>
#include <random>

const int K = 75;
using T = array<short, K>;
ostream &operator<<(ostream& os, T t) {
  for (int i = 0; i < K; i++) os << t[i] << " ";
  return os << endl;
}
T fn(T a, T b) {
  T r;
  for (int i = 0; i < K; i++) r[i] = min(a[i], b[i]);
  return r;
}
int a[N];
T v[N], x[N], t0;
short sgn(short x, short y) { return (x > y) - (x < y); }
void ac() {
  int n, q; cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> a[i];
  Tree<int> t(n);
  t.input().root(1);
  auto h = HLD(t, t0);
  h.fn(fn).hld();
  for (int i = 1; i <= n; i++) x[h.I[i]] = v[a[i]];
  h.sgt.build(x);
  int c = 0;
  while (q--) {
    int t = 0, w = 0, x = 0, y = 0, z = 0; cin >> t >> w >> x;
    if (t == 2) cin >> y >> z;
    w ^= c, x ^= c, y ^= c, z ^= c;
    if (t == 1) { assert(x <= n); h.upd(w, v[x]); }
    else {
      T a = h.query(w, x), b = h.query(y, z);
      int d = 0; for (int i = 0; i < K; i++) d += sgn(a[i], b[i]);
      cout << (d < 0 ? "Yes\n" : "No\n");
      c += (d < 0);
    }
  }
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<> d(SHRT_MIN, SHRT_MAX);
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int i = 1; i < N; i++) for (short&x : v[i]) x = d(rng);
  t0.fill(SHRT_MAX);
  int t; cin >> t;
  while (t--) ac();
}
