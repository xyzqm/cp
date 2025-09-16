// https://oj.uz/problem/view/COCI16_burza
#include <bits/stdc++.h>
using namespace std;

const int K = 20;

int32_t main() {
    int n, k; cin >> n >> k;
    auto report = [](string str) { println("{}", str); exit(0); };
    if (k >= K) report("DA");
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<array<int, K>> acs(n + 1);
    vector<int> l(n + 1), r(n + 1), leaves;
    auto dfs = [&](this auto dfs, int x = 1, int p = 0, int d = -1) -> void {
        acs[x] = acs[p];
        if (d >= 0) acs[x][d] = x;
        l[x] = r[x] = leaves.size();
        if (d == k - 1) {
            leaves.push_back(x);
            ++r[x];
        }
        for (int y : g[x]) if (y != p) {
            dfs(y, x, d + 1);
            r[x] = r[y];
        }
    };
    dfs();
    vector<int> dp(1 << k);
    for (int i = 0; i < 1 << k; i++) {
        if (dp[i] == leaves.size()) report("DA");
        for (int j = 0; j < k; j++) if (!(i >> j & 1)) {
            dp[i ^ (1 << j)] = max(dp[i ^ (1 << j)], r[acs[leaves[dp[i]]][j]]);
        }
    }
    report("NE");
}
