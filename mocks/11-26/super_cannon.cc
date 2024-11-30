#include <bits/stdc++.h>
#include "mint.h"
#define int long long
using namespace std;

const int M = 2333;
mint p[M]; // p[i] = sum{0...i} nCj

mint ac() {
    int n, k; cin >> n >> k;
    mint x = p[0] = 1;
    for (int i = 1; i < M; i++) {
        p[i] = p[i - 1] + (x *= mint{n - i + 1} / i);
    }
    if ((k = min(k, n)) < M) return p[k];
    cout << x << endl;
    x *= mint{n - M + 1} / M; // x = nCM
    return p[M - 1] * (mint{1} - x.exp(k / M + 1) / (mint{1} - x)) + x.exp(k / M + 1) * p[k % M];
}

signed main() {
    int t; cin >> t;
    while (t--) cout << ac() << endl;
}
