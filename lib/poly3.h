#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma once
#include <bits/stdc++.h>
using namespace std;
#include "mint.h"

const int M = 998244353;
const int K = 23; // largest power of 2 that divides M - 1

// polynomial
using T = mint;
struct F : vector<T> {
    inline static T w = mint{3}.exp((M - 1) / (1 << K));
    inline static T i2 = mint{2}.inv();
    inline static vector<T> p{w}, ip{w.inv()};
    // primitives
    using vector<T>::vector; // inherit all constructors!
    F& resize(size_t sz) { return vector<T>::resize(__bit_ceil(sz)), *this; }
    F(size_t sz) : vector<T>(__bit_ceil(sz)) {}
    F slice(size_t sz) const {
        F f(begin(), begin() + min(sz = __bit_ceil(sz), size()));
        return f.resize(sz);
    }
    static void nft(bool type, F& a) {
        while (K >= p.size()) {
            p.push_back(p.back() * p.back());
            ip.push_back(ip.back() * ip.back());
        }
        int n = int(a.size()), s = 0;
        while ((1 << s) < n) s++;
        assert(1 << s == n);
        F b(n);
        for (int i = 1; i <= s; i++) {
            int w = 1 << (s - i);
            mint base = type ? ip[K - i] : p[K - i], now = 1;
            for (int y = 0; y < n / 2; y += w) {
                for (int x = 0; x < w; x++) {
                    auto l = a[y << 1 | x];
                    auto r = now * a[y << 1 | x | w];
                    b[y | x] = l + r;
                    b[y | x | n >> 1] = l - r;
                }
                now *= base;
            }
            ::swap(a, b);
        }
    }
    // FFT
    F& ntt(bool inv = false) { // inplace fft/ifft
        while (K >= p.size()) {
            p.push_back(p.back() * p.back());
            ip.push_back(ip.back() * ip.back());
        }
        for (int _ = 0; (1 << _) < size(); _++) {
            int s = inv ? 1 << _ : size() >> 1 >> _; // stride
            assert(s < (1 << K));
            int e = (1 << (K - 1)) / s;
            T dw = (inv ? ip : p)[__builtin_ctz(e)];
            for (int i = 0; i < size(); i += s << 1) {
                T W = 1;
                for (int j = 0; j < s; j++) {
                    T x = at(i | j), y = at(i | j | s);
                    tie(at(i | j), at(i | j | s)) = inv ?
                        make_tuple((x + y * W) * i2, (x - y * W) * i2) :
                        make_tuple(x + y, (x - y) * W);
                    W = W * dw;
                }
            }
        }
        return *this;
    }
    // cout override
    friend ostream& operator<<(ostream& os, F f) {
        for (mint x : f) os << x << " ";
        return os;
    }
    // operations
    F& operator+=(const F &o) {
        for (int i = 0; i < min(size(), o.size()); i++) at(i) += o.at(i);
        return *this;
    }
    F operator+(const F &o) const { return F(*this) += o; }
    F& operator+=(int v) { at(0) += v; return *this; }
    F operator+(int v) const { return F(*this) += v; }
    F& operator*=(const F &o) {
        int n = max(size(), o.size()) << 1;
        resize(n);
        F b = o.slice(n);
        // nft(false, *this), nft(false, b);
        ntt(), b.ntt();
        for (int i = 0; i < n; i++) at(i) *= b[i];
        // nft(true, *this);
        // mint iz = mint{1} / n;
        // for (int i = 0; i < n; i++) at(i) *= iz;
        // return *this;
        return ntt(true);
    }
    F& operator*=(int v) { for (T &x : *this) x *= v; return *this; }
    F operator*(int v) const { return F(*this) *= v; }
    F operator*(const F &o) const { return F(*this) *= o; }
    F operator/=(const F &o) { return *this *= o.inv(); }
    F operator/(const F &o) const { return F(*this) /= o; }
    // inverse
    F inv() const {
        if (!at(0).v) throw logic_error("cannot invert polynomial with f(0) == 0");
        F g{at(0).inv()};
        for (int k = 2; k <= size(); k <<= 1) {
            g.resize(k << 1).ntt();
            F h = slice(k).resize(k << 1).ntt();
            for (int i = 0; i < k << 1; i++) {
                g[i] *= mint{2} - g[i] * h[i];
            }
            g.ntt(true).resize(k);
        }
        return g;
    }
};
