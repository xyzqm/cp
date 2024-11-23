#include <bits/stdc++.h>
#include "mint.h"
using namespace std;

const int M = 998244353;
const int K = 23; // largest power of 2 that divides M - 1

template <typename T>
void fft(vector<T> f, bool inv = false) { // inplace fft/ifft
    for (int _ = 0; (1 << _) < f.size(); _++) {
        int s = inv ? 1 << _ : f.size() >> 1 >> _; // stride
        mint dw = w.exp(N / s);
        if (inv) dw = dw.inv();
        mint W = 1;
        // cout << s << " " << dw << endl;
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
    if (inv) for (int i = 0; i < n; i++) a[i] = f[i];
}
