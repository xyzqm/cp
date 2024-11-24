#include <bits/stdc++.h>
#include "poly2.h"
#include "combo.h"

const int N = 6e6 + 1;

F f, g, gf;
Combo<N, M> C;
mint ctln(int n) { return C.C(2 * n, n) / (n + 1); }
int c[N];

int main() {
    int n; mint k; cin >> n >> k;
    f.resize(n + 1), g.resize(n + 1);
    g[1] = k;
    // gcd has to be either 2 * n or <= n
    for (int i = 1; 2 * i <= n; i++) {
        f[2 * i] = ctln(i - 1) * k * (k - 1).exp(i - 1);
        g[i * 2 + 1] = C.C(2 * i, i) * k * (k - 1).exp(i);
    }
    gf = (f / (f * -1 + 1) + 1).slice(n) * (g + 1); // [i] -> # of colorings for RBS + extra stuff of len i
    for (int i = 1; i <= 2 * n; i++) ++c[gcd(i, 2 * n)];
    for (int i = 1; i <= n; i++) gf[2 * n] += mint{i} / (2 * n - i) * C.C(2 * n - i, n) * (k - 1).exp(n - i) * k.exp(i);
    mint r = 0;
    for (int i = 1; i <= 2 * n; i++) {
        r += gf[i] * c[i];
    }
    cout << r / (2 * n) << endl;
}
