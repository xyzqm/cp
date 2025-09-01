#include <bits/stdc++.h>
using namespace std;

void ac() {
    int n; cin >> n;
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> frq(n + 1), frq_d(n + 1);
    auto dfs = [&](this auto dfs, int x, int p, int d) -> int {
        ++frq[d];
        int mx = d;
        for (int y : g[x]) if (y != p) mx = max(mx, dfs(y, x, d + 1));
        ++frq_d[mx];
        return mx;
    };
    dfs(1, 0, 0);
    for (int i = n; i --> 0; ) frq[i] += frq[i + 1];
    for (int i = 1; i <= n; i++) frq_d[i] += frq_d[i - 1];
    int ans = n;
    for (int i = 0; i < n; i++) {
        ans = min(ans, frq[i + 1] + (i > 0 ? frq_d[i - 1] : 0));
    }
    cout << ans << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
