#pragma once
#include <bits/stdc++.h>
#include "mint.h"

const int M = 998244353;
const int K = 23; // largest power of 2 that divides M - 1

// polynomial
using T = mint;
struct F : vector<T> {
    inline static T w = mint{3}.exp((M - 1) / (1 << K));
    inline static T i2 = mint{2}.inv();
    // primitives
    F& resize(size_t sz) { return vector<T>::resize(__bit_ceil(sz)), *this; }
    F slice(size_t sz) const {
        F g; g.resize(sz);
        for (int i = 0; i < min(size(), g.size()); i++) g[i] = at(i);
        return g;
    }
    F(initializer_list<T> l = {}) : vector<T>(l) {}
    F(int n) : vector<T>(1, n) {}
    // F(size_t n) : vector<T>(__bit_ceil(n)) {}
    // FFT
    F& fft(bool inv = false) { // inplace fft/ifft
        for (int _ = 0; (1 << _) < size(); _++) {
            int s = inv ? 1 << _ : size() >> 1 >> _; // stride
            assert(s < (1 << K));
            T dw = w.exp((1 << (K - 1)) / s);
            if (inv) dw = dw.inv();
            T W = 1;
            for (int i = 0; i < size(); i++) if (!(i & s)) {
                W = (i & (s - 1) ? W * dw : 1);
                T x = at(i), y = at(i | s);
                tie(at(i), at(i | s)) = inv ?
                    make_tuple((x + y * W) * i2, (x - y * W) * i2) :
                    make_tuple(x + y, (x - y) * W);
            }
        }
        return *this;
    }
    //
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
    F operator*=(const F &o) {
        int n = 2 * max(size(), o.size());
        resize(n);
        F b = o.slice(n);
        fft(), b.fft();
        for (int i = 0; i < n; i++) at(i) *= b[i];
        return fft(true);
    }
    // F& operator*=(int v) { for (T &x : *this) x *= v; return *this; }
    // F operator*(int v) const { return F(*this) *= v; }
    // F& operator+=(int v) { for (T &x : *this) x += v; return *this; }
    // F operator+(int v) const { return F(*this) += v; }
    F operator*(const F &o) const { return F(*this) *= o; }
    F operator/=(const F &o) { return *this *= o.inv(); }
    F operator/(const F &o) const { return F(*this) /= o; }
    // inverse
    F inv() const {
        if (!at(0).v) throw logic_error("cannot invert polynomial with f(0) == 0");
        F g{at(0).inv()};
        for (int k = 2; k <= size(); k <<= 1) {
            g *= ((slice(k) * g).resize(k) * -1 + 2);
            g.resize(k);
        }
        return g;
    }
};
