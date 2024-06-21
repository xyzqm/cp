#include <array>
#include <cassert>
#include <iostream>
#include <utility>
using namespace std;
const int N = 1 << 19;

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

const mint i2 = mint(2).inv();

template <int N> struct F {
  static inline const mint w = mint(3).E((mint::M - 1) / N);
  static inline const mint iw = w.inv();
  static inline mint p[N]{}, ip[N]{};
  array<mint, N> a{};
  F<N>() {
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
        mint x = a[i], y = a[i + s];
        if (inv) a[i] = (x + y * W) * i2, a[i + s] = (x - y * W) * i2;
        else a[i] = x + y, a[i + s] = (x - y) * W;
      }
    } 
    return *this;
  }
  mint& operator[](int i) { return a[i]; }
  // pointwise multiplication
  void operator*= (F<N>& f) { for (int i = 0; i < N; i++) a[i] = a[i] * f[i]; }
  // pointwise multiplication by scalar
  F<N> operator* (const mint &v) const { F<N> f = *this; for (int i = 0; i < N; i++) f[i] = f[i] * v; return f; }
  // addition by scalar
  F<N> operator+ (const mint& v) const { F<N> f = *this; f[0] = f[0] + v; return f; }
  // convolution
  F<N << 1> operator* (const F<N> &&o) const {
    F<N << 1> A = slice<N << 1>(), B = o.template slice<N << 1>();
    A.fft() *= B.fft();
    return A.fft(true);
  }
  F<N> *v;
  // multiplicative inverse (mod x^N)
  template <int K = 1>
  inline constexpr void inv_internal(F<K> &&f) {
    if constexpr (K == N) *v = f;
    else {
      if constexpr (K == 1) f[0] = a[0].inv();
      F<K << 1> h;
      {
        auto F = f.template slice<K << 1>();
        auto g = F * (F * slice<K << 1>() * -1 + 2).template slice<K << 1>();
        h = g.template slice<K << 1>();
      }
      inv_internal<K << 1>(std::move(h));
    }
  }
  F<N> inv() {
    v = new F<N>(); F<1> f; inv_internal(std::move(f));
    return *v;
  }
};


signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  F<N> f;
  int n; cin >> n;
  for (int i = 0; i < n; i++) cin >> f[i];
  F<N> h = f.inv();
  for (int i = 0; i < n; i++) cout << h.a[i] << " ";
  cout << endl;
}

