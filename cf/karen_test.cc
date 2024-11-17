// https://codeforces.com/contest/815/problem/B
#include <cassert>
#include <iostream>
#include <vector>
#define int long long
#define exit(X) { cout << (X); return; }
using namespace std;
const int inf = 1e18;

const int N = 2e5 + 1;

struct mint;
using P = pair<mint, mint>;
struct mint {
  const static int M = 1e9 + 7;
  int v = 0;
  mint() {}
  mint(int v) { this->v = (v % M + M) % M; assert(this->v >= 0); }
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
};
mint F[N], F_i[N];
void pre(int n) { F[0] = F_i[0] = 1; for (int i = 1; i < n; i++) F_i[i] = (F[i] = F[i - 1] * i).inv(); }
mint C(int n, int k) { return F[n] * F_i[n - k] * F_i[k]; }

mint ac(vector<mint> v) {
  int n = v.size() - 1;
  assert(n & 1);
  mint r = 0;
  for (int i = 0; i <= n; i++) {
    r += v[i] * C(n / 2, (n - i) / 2) * (i & 1 ? (n % 4 == 1 ? 1 : -1) : 1);
  }
  return r;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  pre(N);
  int n; cin >> n;
  vector<mint> v(n);
  for (mint &x : v) cin >> x;
  if (n == 1) { cout << v[0] << endl; return 0;}
  if (n & 1) {
    for (int i = 0; i < n - 1; i++) v[i] = (i & 1 ? v[i] - v[i + 1] : v[i] + v[i + 1]);
    v.resize(n - 1);
  }
  cout << ac(v) << endl;
}
