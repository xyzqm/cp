// https://judge.yosupo.jp/problem/convolution_mod
#include <bits/stdc++.h>
#include "poly2.h"

int main() {
    int n, m; cin >> n >> m;
    F f, g;
    for (int i = 0; i < n; i++) cin >> f[i];
    for (int i = 0; i < m; i++) cin >> g[i];
    F h = f * g;
    for (int i = 0; i < n + m - 1; i++) cout << h[i] << " ";
    cout << endl;
}
