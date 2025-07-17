#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int N = 2e3 + 2;

int n, x, a[N], c[N];
vector<int> g[N];

int req(int x, int p) {
    int r = 0;
    for (int y : g[x]) if (y != p) r += req(y, x);
    if (c[x] - r < a[x]) return a[x] - (c[x] - r);
    else if ((c[x] - r - a[x]) % 2) return 1;
    else return 0;
}

// check whether it's possible to have k full rounds
// returns # of additional steps required
int ck(int k) {
    for (int i = 1; i <= n; i++) c[i] = k;
    for (int i = 0; i <= n; i++) {
        int v = req(x, 0);
        // cout << k << " " << i << " " << v << endl;
        if (v <= 0 && abs(v) % 2 == 0) return i;
        ++c[i + 1];
    }
    return -1;
}

int ac() {
    cin >> n >> x;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int k0 = 2e9, k1 = 2e9 - 1;
    for (int d = (1LL << 31); d > 1; d /= 2) {
        if (ck(k0 - d) >= 0) k0 -= d;
        if (ck(k1 - d) >= 0) k1 -= d;
    }
    return min(k0 * n + ck(k0), k1 * n + ck(k1));
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << ac() << endl;
}
