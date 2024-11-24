#include <bits/stdc++.h>
#include "mint.h"
using namespace std;
const int M = 998244353;

const mint i2 = mint(2).inv(); // self-explanatory

using poly = vector<int>;

// make sure N is a power of two!
template <int N>
struct F {
    inline static mint w = mint(3).exp((M - 1) / (N << 1));
    inline static mint iw = w.inv();
    mint a[N << 1]{}, f[N << 1]{}; // a is actual array, f is for fft values
    int n = 1; // should always be power of two
    F(initializer_list<mint> l = {}, bool t = false) {
        assert(l.size() <= N && __builtin_popcount(N) == 1);
        int i = 0; for (mint x : l) a[i++] = x;
        while (n < l.size()) n <<= 1;
    }
    F& rsz(int k, bool e = false) { assert(k <= (N << 1));
        if (e) for (int i = k; i < n; i++) a[i] = 0; n = k; return *this;
    }
    F slice(int k, bool e = false) { assert(k <= (N << 1));
        return F(*this).rsz(k, e);
    }
    F& fft(int n = 0, bool inv = false) {
        if (!n) n = this->n;
        if (!inv) for (int i = 0; i < n; i++) f[i] = i < this->n ? a[i] : 0;
        for (int _ = 0; (1 << _) < n; _++) {
            int s = inv ? 1 << _ : n >> 1 >> _; // stride
            mint dw = w.exp(N / s);
            if (inv) dw = dw.inv();
            mint W = 1;
            for (int i = 0; i < n; i++) if (!(i & s)) {
                // cout << W << " " << (inv ? ip : p)[N / s * (i & (s - 1))] << endl;
                W = (i & (s - 1) ? W * dw : 1);
                // cout << (i & (s - 1)) << ":" << W << ":" << (inv ? ip : p)[N / s * (i & (s - 1))] << " ";
                mint x = f[i], y = f[i | s];
                if (inv) f[i] = (x + y * W) * i2, f[i | s] = (x - y * W) * i2;
                else f[i] = x + y, f[i | s] = (x - y) * W;
            }
            // cout << endl;
        }
        for (int i = 0; i < n; i++) cout << f[i] << " \n"[i == n - 1];
        if (inv) for (int i = 0; i < n; i++) a[i] = f[i];
        return *this;
    }
    F& ifft(int n = 0) { if (!n) n = this->n; return fft(n, true); }
    mint& operator[](int i) { while (i >= n) n <<= 1; return a[i]; }
    // pointwise multiplication of fft coeffs
    F& dot(F &g) { for (int i = 0; i < n; i++) f[i] = f[i] * g.f[i]; return *this; }
    // right shift (multiply by x^k)
    F& operator>>=(int k) { for (int i = n; i --> 0; ) a[i] = (i < k ? 0 : a[i - k]); return *this; }
    // left shift (divide by x^k)
    F& operator<<=(int k) { for (int i = 0; i < n; i++) a[i] = (i + k < n ? a[i + k] : 0); return *this; }
    // multiplication by scalar
    F& operator*= (const mint v) { for (int i = 0; i < n; i++) a[i] = a[i] * v; return *this; }
    F operator* (const mint v) {
        return F(*this) *= v;
    }
    // addition by scalar
    F& operator+= (const mint &v) { a[0] = a[0] + v; return *this; }
    F operator+ (const mint &v) {
       return F(*this) += v;
    }
    // adding two polynomials
    F& operator+= (F o) { for (int i = 0; i < min(n, o.n); i++) a[i] = a[i] + o[i]; return *this; }
    F operator+ (F o) {
        return F(*this) += o;
    }
    // convolution
    F& operator*= (F o) {
        int k = max(n, o.n) << 1; assert(k <= (N << 1));
        return fft(k).rsz(k).dot(o.fft(k)).ifft();
    }
    F operator* (F o) {
        return F(*this) *= o;
    }
    friend ostream& operator<<(ostream& s, F f) {
        for (int i = 0; i < f.n; i++) cout << f[i] << " ";
        return s;
    }
    // multiplicative inverse (mod x^N)
    F inv() {
        if (!a[0].v) throw logic_error("cannot invert polynomial with f(0) == 0");
        F g{a[0].inv()};
        int n = this->n;
        for (int k = 2; k <= n; k <<= 1) {
            g *= (slice(k) * g).slice(k) * -1 + 2;
            g.slice(k);
        }
        return g;
    }
    F operator/(F f) { F g = f.inv(); return *this * g; }

    #ifdef SQRT
    F sqrt() {
        int i = 0; while (i < n && !a[i].v) i++;
        if (i == n) return F(n);
        else if (i & 1 || a[i].sym().v != 1) throw logic_error("this polynomial does not have a square root");
        F f = *this, g = F{a[i].sqrt()};
        f <<= i;
        int n = this->n;
        for (int k = 2; k <= n; k <<= 1) {
            g.slice(k);
            g += f.slice(k) / g;
            g *= i2;
        }
        return g >>= (i >> 1);
    }
    #endif
    // derivative
    F d() {
        F r;
        for (int i = 0; i < n - 1; i++) r[i] = mint(i + 1) * a[i + 1];
        r[n] = 0;
        return r.slice(n);
    }
    // integral
    F i() {
        F r;
        for (int i = n; i --> 1; ) r[i] = a[i - 1] / i;
        r[0] = 0;
        return r.slice(n);
    }

    F ln() { F g = inv(); return (g * d()).slice(n).i(); }

    F exp() {
        if (a[0].v) throw logic_error("f(0) must be 0 for e^f to exist");
        F g = F{1};
        int n = this->n;
        for (int k = 2; k <= n; k <<= 1) {
            g.slice(k);
            F h = g.ln() * -1;
            g *= slice(k) + h + 1;
        }
        return g;
    }
    F operator^(int x) {
        F f = *this;
        int i = 0; while (i < n && !f[i].v) i++;
        if (i == n) return x ? F{0} : F{1};
        f <<= i;
        mint a = f[0]; f *= a.inv();
        F g = f.ln() * x;
        F h = g.exp() * a.exp(x);
        return h >>= (min(x, N) * i);
    }
};

#ifdef POLY
mint a[N];
// some template driver functions
void convolve() {
    int n, m; cin >> n >> m;
    F f(n), g(m);
    for (int i = 0; i < n; i++) cin >> f[i];
    for (int i = 0; i < m; i++) cin >> g[i];
    cout << (f *= g).slice(n + m - 1) << endl;
}
void pow() {
    int n, k; cin >> n >> k;
    F f(n);
    for (int i = 0; i < n; i++) cin >> f[i];
    cout << (f ^ k).slice(n) << endl;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    /* convolve(); return 0; */
    pow(); return 0;
    int n; cin >> n;
    F f(n); for (int i = 0; i < n; i++) cin >> f[i];
    try { cout << f.exp().slice(n) << endl; } catch (logic_error e) { cout << e.what() << endl; cout << -1 << endl; }
}
#endif
