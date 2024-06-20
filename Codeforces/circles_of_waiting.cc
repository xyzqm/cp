// https://codeforces.com/problemset/problem/963/E
#include <cassert>
#include <iostream>
#include <numeric>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e2 + 2;

const int M = 1e9 + 7;
int E(int x, int y) { int r = 1; for (y <<= 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x % M; return r; }
int inv(int x) { return E(x, M - 2); }
int sb(int x, int y) { return ((x - y) % M + M) % M; }
int ad(int x, int y) { return (x % M + y % M) % M; }

template <int... D> struct T {
  int v = 0;
  void operator*= (int x) { v = v * x % M; }
  void operator+= (int x) { v = ad(v, x); }
  void operator-= (int x) { v = sb(v, x); }
  void operator+= (T<> x) { *this += x.v; }
  void operator-= (T<> x) { *this -= x.v; }
  void operator= (int x) { v = x; }
  string str() { return to_string(v); }
};
template <int N, int... D> struct T<N, D...> {
  T<D...> a[N];
  T<N, D...> operator* (int v) {
    auto o = *this;
    for (int i = 0; i < N; i++) o[i] *= v;
    return o;
  }
  void operator*= (int v) { *this = *this * v; }
  T<N, D...> operator+ (T<N, D...> b) {
    auto o = *this;
    for (int i = 0; i < N; i++) o[i] += b[i];
    return o;
  }
  void operator+= (T<N, D...> b) { *this = *this + b; }
  void operator-= (T<N, D...> b) {
    for (int i = 0; i < N; i++) a[i] -= b[i];
  }
  T<D...>& operator[] (int i) { return a[i]; }
  string str() {
    string s = "";
    for (int i = 0; i < N; i++) s += a[i].str() + (sizeof...(D) ? "\n" : " ");
    return s;
  }
  void gauss(int n) {
    for (int i = 0; i <= n; i++) {
      if (!a[i][i].v) {
        int r = i; 
        for (int j = i + 1; j <= n; j++) if (a[j][i].v) r = j; 
        assert(a[r][i].v);
        swap(a[i], a[r]);
      }
      a[i] *= inv(a[i][i].v);
      for (int j = 0; j <= n; j++) if (j != i) {
        a[j] += a[i] * (M - a[j][i].v);
      }
    }
  }
};

int R;
bool I(int x, int y) { return (R - x) * (R - x) + (R - y) * (R - y) <= R * R; }

int a[4], p[4];
T<N> v[N][N];
T<N, N> f;

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> R;
  for (int i = 0; i < 4; i++) cin >> a[i];
  int s = accumulate(a, a + 4, 0);
  for (int i = 0; i < 4; i++) p[i] = a[i] * inv(s) % M; 
  for (int i = 0; i <= 2 * R; i++) {
    for (int j = 0; j <= 2 * R; j++) if (I(i, j)) {
      if (!I(i - 1, j)) v[i][j][j] = 1;
      else {
        v[i][j] = v[i - 1][j];
        if (i >= 2)  v[i][j] -= v[i - 2][j] * p[0];
        if (j) v[i][j] -= v[i - 1][j - 1] * p[1];
        v[i][j] -= v[i - 1][j + 1] * p[3];
        v[i][j][2 * R + 1] -= 1;
        v[i][j] *= inv(p[2]);
      }
      if (!I(i + 1, j)) {
        f[j] = v[i][j]; 
        if (i) f[j] -= v[i - 1][j] * p[0];
        if (j) f[j] -= v[i][j - 1] * p[1];
        f[j] -= v[i + 1][j] * p[2] + v[i][j + 1] * p[3];
        f[j][2 * R + 1] -= 1;
        f[j][2 * R + 1] = (M - f[j][2 * R + 1].v) % M;
      }
    }
  }
  for (int i = 0; i <= 2 * R; i++) for (int j = 0; j <= 2 * R; j++) if (I(i, j) && !I(i + 1, j)) {
      f[j] = v[i][j]; 
      if (i) f[j] -= v[i - 1][j] * p[0];
      if (j) f[j] -= v[i][j - 1] * p[1];
      f[j] -= v[i + 1][j] * p[2] + v[i][j + 1] * p[3];
      f[j][2 * R + 1] -= 1;
      f[j][2 * R + 1] = (M - f[j][2 * R + 1].v) % M;
    }
  f.gauss(2 * R);
  int r = 0;
  for (int i = 0; i <= 2 * R; i++) r = ad(r, v[R][R][i].v * f.a[i][2 * R + 1].v);
  cout << ad(r, v[R][R][2 * R + 1].v) << endl;
}
