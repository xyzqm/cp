// https://codeforces.com/problemset/problem/285/E
#include <cassert>
#include <iostream>
#define int long long
#define exit(X) { cout << (X); return; }
using namespace std;
const int inf = 1e18;

const int N = 1e3 + 1;

struct mint;
using P = pair<mint, mint>;
struct mint {
  const static int M = 1e9 + 7;
  int v = 0;
  mint() {}
  mint(int v) { this->v = (v % M + M) % M; }
  mint operator+(const mint &o) const { return v + o.v; }
  mint& operator+=(const mint& o) { v = (v + o.v) % M; return *this; }
  mint operator*(const mint &o) const { return v * o.v; }
  mint operator-(const mint &o) const { return v - o.v; }
  mint& operator-=(const mint& o) { mint t = v - o.v; v = t.v; return *this; }
  mint operator^(int y) const { mint r = 1, x = v; for (y <<= 1; y >>= 1; x = x * x) if (y & 1) r = r * x; return r; }
  mint inv() const { assert(v); return *this ^ M - 2; }
  mint sym() { return *this ^ (M - 1) / 2; } // legendre symbol: 1 -> qresidue, -1 -> non-residue
  friend istream& operator>>(istream& s, mint& v) { s >> v.v; return s; }
  friend ostream& operator<<(ostream& s, const mint& v) { s << v.v; return s; }
  mint sqrt() {
    if (!v) return 0;
    mint i = 1;
    while ((i * i - v).sym().v != M - 1) i = i + 1;
    mint w = i * i - v;
    auto mul = [&](P x, P y) { return P{
      x.first * y.first + x.second * y.second * w,
      x.first * y.second + x.second * y.first
    }; }; 
    P c = {i, 1}, r = {1, 0};
    for (int i = 1; i < 2 * M; i <<= 1) {
      if (((M + 1) / 2) & i) r = mul(r, c);
      c = mul(c, c);
    }
    assert(r.second.v == 0 && (r.first * r.first).v == v);
    if (r.first.v < M / 2) return r.first;
    return r.first * -1;
  }
  mint operator/(mint o) { return *this * o.inv(); }
} dp[N][N][2][2], f[N];

mint F[N], F_i[N];
void pre(int n) { F[0] = F_i[0] = 1; for (int i = 1; i < n; i++) F_i[i] = (F[i] = F[i - 1] * i).inv(); }
mint C(int n, int k) { return F[n] * F_i[n - k] * F_i[k]; }

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  pre(N);
  int n, k; cin >> n >> k;
  dp[0][0][1][0] = 1;
  auto sum = [&](int i, int j, int k, int h) {
    mint s = 0;
    for (int x = 0; x < 2; x++) if (x == k || k == 2) for (int y = 0; y < 2; y++) if (y == h || h == 2) s += dp[i][j][x][y];
    return s;
  };
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k < 2; k++) for (int h = 0; h < 2; h++) {
        if (!h) dp[i][j][k][h] += sum(i - 1, j, 2, k); // don't place i
        if (j && i > 1 && !h) dp[i][j][k][h] += dp[i - 1][j - 1][0][k]; // place i at position i - 1
        if (j && i < n && h) dp[i][j][k][h] += sum(i - 1, j - 1, 2, k); // place i at position i + 1
      }
    }
  }
  for (int i = n; i >= 0; i--) {
    for (int k = 0; k < 2; k++) f[i] += dp[n][i][k][0] * F[n - i];
    for (int j = i + 1; j <= n; j++) f[i] -= f[j] * C(j, i);
    /* cout << i << " " << f[i] << endl; */
  }
  cout << f[k] << endl;
}
