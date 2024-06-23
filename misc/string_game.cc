// https://loj.ac/p/6436
#include <iostream>
#include <cassert>
#include <array>
#include <string>
#include <vector>
#define exit(X) { cout << (X); return; }
using namespace std;

const int N = 1 << 19;

using ll = long long;
struct mint;
using P = pair<mint, mint>;
struct mint {
  const static ll M = 998244353;
  ll v = 0;
  mint() {}
  mint(ll v) { this->v = (v % M + M) % M; }
  mint operator+(const mint &o) const { return v + o.v; }
  mint operator*(const mint &o) const { return v * o.v; }
  mint operator-(const mint &o) const { return v - o.v; }
  mint E(ll y) const { mint r = 1, x = v; for (y <<= 1; y >>= 1; x = x * x) if (y & 1) r = r * x; return r; }
  mint inv() const { return E(M - 2); }
  mint sym() { return E((M - 1) / 2); } // legendre symbol: 1 -> qresidue, -1 -> non-residue
  friend istream& operator>>(istream& s, mint& v) { s >> v.v; return s; }
  friend ostream& operator<<(ostream& s, const mint& v) { s << v.v; return s; }
  mint sqrt() {
    if (!v) return 0; 
    mint i = 1; while ((i * i - v).sym().v != M - 1) i = i + 1;
    mint w = i * i - v;
    auto mul = [&](P x, P y) { return P{
      x.first * y.first + x.second * y.second * w,
      x.first * y.second + x.second * y.first
    }; }; 
    P c = {i, 1}, r = {1, 0};
    for (ll i = 1; i < 2 * M; i <<= 1) {
      if (((M + 1) / 2) & i) r = mul(r, c);
      c = mul(c, c);
    }
    assert(r.second.v == 0 && (r.first * r.first).v == v);
    if (r.first.v < M / 2) return r.first;
    return r.first * -1;
  }
  mint operator/(mint o) { return *this * o.inv(); }
};

const mint i2 = mint(2).inv();

template <int N> struct F {
  static inline const mint w = mint(3).E((mint::M - 1) / N);
  static inline const mint iw = w.inv();
  static inline mint p[N]{}, ip[N]{};
  array<mint, N> a{};
  F<N>(initializer_list<mint> l = {}) {
    assert(!l.size() || l.size() == N);
    int i = 0; for (mint x : l) a[i++] = x;
    if (p[0].v) return;
    p[0] = 1; for (int i = 1; i < N; i++) p[i] = p[i - 1] * w; 
    ip[0] = 1; for (int i = 1; i < N; i++) ip[i] = ip[i - 1] * iw;
  }
  template<int K>
  F<K> slice() const { F<K> f; for (int i = 0; i < min(K, N); i++) f[i] = a[i]; return f; }
  F<N>& fft(bool inv = false) {
    for (int _ = 1; _ < N; _ <<= 1) {
      int s = inv ? _ : N / 2 / _; // stride
      for (int i = 0; i < N; i++) if (!(i & s)) {
        mint W = (inv ? ip : p)[N / 2 / s * (i & (s - 1))];
        mint x = a[i], y = a[i | s];
        if (inv) a[i] = (x + y * W) * i2, a[i | s] = (x - y * W) * i2;
        else a[i] = x + y, a[i | s] = (x - y) * W;
      }
    } 
    return *this;
  }
  mint& operator[](int i) { return a[i]; }
  const mint& operator[](int i) const { return a[i]; }
  // pointwise multiplication
  void operator*= (F<N> &f) { for (int i = 0; i < N; i++) a[i] = a[i] * f[i]; }
  // multiplication by scalar
  void operator*= (const mint &v) { for (int i = 0; i < N; i++) a[i] = a[i] * v; }
  F<N> operator* (const mint &v) const { F<N> f = *this; f *= v; return f; }
  // addition by scalar
  void operator+= (const mint &v) { a[0] = a[0] + v; }
  F<N> operator+ (const mint &v) const { F<N> f = *this; f += v; return f; }
  // adding two polynomials
  template <int K>
  F<N> operator+ (const F<K> &&o) const { F<N> f = *this; for (int i = 0; i < min(N, K); i++) f[i] = f[i] + o[i]; return f; } 
  // convolution
  F<N << 1> operator* (const F<N> &o) const {
    F<N << 1> A = slice<N << 1>(), B = o.template slice<N << 1>();
    A.fft() *= B.fft();
    return A.fft(true);
  }
  friend ostream& operator<<(ostream& s, F<N> f) {
    cout << N << ": ";
    for (int i = 0; i < N; i++) cout << f[i] << " ";
    return s;
  }
  // multiplicative inverse (mod x^N)
  template <int K>
  F<K << 1> invl(F<K> &&f) {
    auto F = f.template slice<K << 1>();
    auto g = F * (F * slice<K << 1>() * -1 + 2).template slice<K << 1>();
    return g.template slice<K << 1>();
  }
  template <int K>
  F<N> inv(F<K> &&f) {
    if constexpr (K == N) return f;
    else return inv<K << 1>(invl(std::move(f)));
    
  }
  F<N> inv() { assert(a[0].v); return inv(F<1>{a[0].inv()}); }

  F<N << 1> operator/(F<N> &f) { return *this * f.inv(); }

  // square root (mod x^N)
  template <int K>
  F<K << 1> sqrtl(F<K> &&f) {
    auto g = f.template slice<K << 1>();
    return (g + (slice<K << 1>() / g)) * i2;
  }
  template <int K>
  F<N> sqrt(F<K> &&f) {
    if constexpr (K == N) return f;
    else return sqrt<K << 1>(sqrtl(std::move(f)));
  }
  F<N> sqrt() { assert(a[0].sym().v == 1); return sqrt(F<1>{a[0].sqrt()}); }
};


signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  F<N> f, g;
  string s; cin >> s;
  int n = s.length();
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') f[i] = 1;
    else if (s[i] == '0') g[n - 1 - i] = 1;
  }
  auto h = f * g;
  vector<bool> r(n + 1, true);
  for (int i = 0; i < 2 * n - 1; i++) if (h[i].v) r[abs(n - 1 - i)] = false;
  for (int i = 1; i <= n; i++) for (int j = i; j <= n; j += i) if (!r[j]) r[i] = false; 
  ll R = 0; for (ll i = 1; i <= n; i++) if (r[n - i]) R ^= i * i;
  cout << R << endl;
}
