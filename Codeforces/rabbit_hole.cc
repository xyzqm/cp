//https://codeforces.com/contest/2028/problem/E
#include <bits/stdc++.h>
#include "mint.h"
using namespace std;
using ll = long long;
#define int ll

const int N = 2e5 + 1;
const int M = 998244353;
vector<int> g[N];
int d[N], mind[N], leaf[N];
mint dp[N];
int dfs(int x, int p) {
    bool leaf = true;
    mind[x] = inf;
    d[x] = d[p] + 1;
    for (int y : g[x]) if (y != p) {
        leaf = false;
        mind[x] = min(mind[x], dfs(y, x));
    }
    if (leaf) mind[x] = d[x];
    ::leaf[x] = leaf;
    return mind[x];
}

void DP(int x, int p) {
    if (x == 1) dp[x] = 1;
    else if (leaf[x]) dp[x] = 0;
    else {
        dp[x] = dp[p] - mint{1 + mind[x] - d[x]}.inv() * dp[p];
    }
    for (int y : g[x]) if (y != p) {
        DP(y, x);
    }
}

void ac() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    DP(1, 0);
    for (int i = 1; i <= n; i++) cout << dp[i] << " ";
    cout << endl;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
