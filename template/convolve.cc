// https://judge.yosupo.jp/problem/convolution_mod
#include <bits/stdc++.h>
#include "poly2.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    F f(n), g(m);
    for (int i = 0; i < n; i++) cin >> f[i];
    for (int i = 0; i < m; i++) cin >> g[i];
    F h = f * g;
    for (int i = 0; i < n + m - 1; i++) cout << h[i] << " ";
    cout << endl;
}
