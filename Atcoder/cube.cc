// https://atcoder.jp/contests/abc198/tasks/abc198_f
#include <iostream>
#include <vector>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int M = 998244353;
int ad(int& x, int y) { return x = (x % M + y % M) % M; }

template <int N, int K> struct T {
  int a[N][K]{};
  template <int D>
  T<N, D> operator*(T<K, D> &o) {
    T<N, D> r;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < D; j++) {
        for (int k = 0; k < K; k++) ad(r.a[i][j], a[i][k] * o.a[k][j] % M);
      }
    }
    return r;
  }
};

int S;

int C(vector<int> v) {
  int n = v.size();
  T<36, 1> a; a.a[35][0] = 1;
  T<36, 36> m;
  for (int i = 0; i < 35; i++) m.a[i][i + 1] = 1;
  for (int i = 1; i < 1 << n; i++) {
    int s = 0; for (int j = 0; j < n; j++) if (i >> j & 1) s += v[j];
    ad(m.a[35][36 - s], __builtin_popcount(i) % 2 ? 1 : M - 1);
  }
  T<36, 36> r; for (int i = 0; i < 36; i++) r.a[i][i] = 1;
  for (int k = (S - 6) << 1; k >>= 1; m = m * m) if (k & 1) r = r * m; 
  return (r * a).a[35][0];
}

signed main() {
  cin >> S;
  int r = 0;
  ad(r, 1 * C({1, 1, 1, 1, 1, 1}));
  ad(r, 6 * C({4, 1, 1}));
  ad(r, 3 * C({2, 2, 1, 1}));
  ad(r, 8 * C({3, 3}));
  ad(r, 6 * C({2, 2, 2}));
  cout << r * 291154603 % M << endl;
}
