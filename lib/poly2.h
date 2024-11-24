#include <bits/stdc++.h>
#include "mint.h"
using namespace std;

const int M = 998244353;
const int K = 23; // largest power of 2 that divides M - 1

// polynomial
using T = mint;
struct F : vector<T> {
    inline static T w = mint{3}.exp((M - 1) / (1 << K));
    inline static T i2 = mint{2}.inv();

    void resize(size_t sz) { vector<T>::resize(__bit_ceil(sz)); }

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

    // data
    T& operator[](int i) {
        if (i >= size()) resize(i + 1);
        return at(i);
    }

    friend ostream& operator<<(ostream& os, F f) {
        for (mint x : f) os << x << " ";
        return os;
    }

    // operations
    F operator*(F &o) const {
        int n = 2 * max(size(), o.size());
        F b = *this; b.resize(n);
        F c = o; c.resize(n);
        b.fft(), c.fft();
        for (int i = 0; i < n; i++) b[i] *= c[i];
        return b.fft(true);
    }
};
