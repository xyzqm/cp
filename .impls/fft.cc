#include <array>
#include <cassert>
#include <iostream>
using namespace std;

const int N = 1 << 20;

using ll = long long;
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
  mint operator/(mint o) { return *this * o.inv(); }
};
istream& operator>>(istream& s, mint& v) { s >> v.v; return s; }
ostream& operator<<(ostream& s, const mint& v) { s << v.v; return s; }

template <int N> struct F {
  array<mint, N> a;
  static inline const mint w = mint(3).E((mint::M - 1) / N);
  static inline const mint iw = w.inv();
  static inline const mint i2 = mint(2).inv();
  static inline mint p[N]{}, ip[N]{};
  F<N>() { 
    if (p[0].v) return;  
    p[0] = 1; for (int i = 1; i < N; i++) p[i] = p[i - 1] * w; 
    ip[0] = 1; for (int i = 1; i < N; i++) ip[i] = ip[i - 1] * iw;
  }
  // in-place fft/ifft
  F<N>& fft(bool inv = false) {
    for (int _ = 1; _ < N; _ <<= 1) {
      int s = inv ? _ : N / 2 / _; // stride
      for (int i = 0; i < N; i++) if (!(i & s)) {
        mint W = (inv ? ip : p)[N / 2 / s * (i & (s - 1))]; 
        mint x = a[i], y = a[i + s];
        if (inv) a[i] = (x + y * W) * i2, a[i + s] = (x - y * W) * i2;
        else a[i] = x + y, a[i + s] = (x - y) * W;
      }
    } 
    return *this;
  }
  // pointwise multiplication
  void operator*= (const F<N>& f) { for (ll i = 0; i < N; i++) a[i] = a[i] * f.a[i]; }
  // convolution
  F<N> operator* (const F<N>& o) {
    F<N> A = *this, B = o;
    A.fft() *= B.fft();
    return A.fft(true);
  }
};


signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  F<N> f, g;
  int n, m; cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> f.a[i];
  for (int i = 0; i < m; i++) cin >> g.a[i];
  F<N> h = f * g;
  for (int i = 0; i < n + m - 1; i++) cout << h.a[i] << " ";
  cout << endl;
}

