#include <bits/stdc++.h>
#include "poly.h"
#include "combo.h"
using namespace std;

#ifndef COMPILED
const int N = 1 << 14;
#else
const int N = 1 << 22;
#endif

F<N> f, g, gf;
Combo<N, M> C;
mint ctln(int n) { return C.C(2 * n, n) / (n + 1); }
int c[N];

int main() {
    int n; mint k; cin >> n >> k;
    g[1] = k;
    for (int i = 1; i <= n; i++) {
        f[2 * i] = ctln(i - 1) * k * (k - 1).exp(i - 1);
        g[i * 2 + 1] = C.C(i * 2, i) * k * (k - 1).exp(i);
    }
    gf = (f / (f * -1 + 1) + 1) * (g + 1); // [i] -> # of colorings for RBS + extra stuff of len i
    for (int i = 1; i <= 2 * n; i++) ++c[gcd(i, 2 * n)];
    mint r = 0;
    for (int i = 1; i <= 2 * n; i++) {
        r += gf[i] * c[i];
    }
    cout << r / (2 * n) << endl;
}
