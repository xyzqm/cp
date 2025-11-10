#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int K = 5;
const int W = 20;
const int M = 998244353;

struct dat {
    int sz = 0;
    array<int, K> mmt; // mmt[k] = sum of x_(i) * i^k
    array<int, W> sm; // sm[w] = sum of x_i for (i = w) mod W
};

inline int mul(const int a, const int b) { return a * b % M; }
inline void ad(int &a, const int b) { a = (a + b) % M; }

dat operator+(int sz, dat d) {
    array<int, K> pw;
    pw[0] = 1;
    for (int i = 1; i < K; i++) pw[i] = mul(pw[i - 1], sz);
    for (int k = K; k --> 0; ) {
        for (int i = 0; i < k; i++) {
            ad(d.mmt[k], mul(d.mmt[i], pw[k - i]));
        }
    }

}
