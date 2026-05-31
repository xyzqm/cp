#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int32_t main() {
    int n, k; cin >> n >> k;
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> sums(k + 1), val(n + 1), s(n + 1), lst(k + 1);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        sums[s[i]] ^= (val[i] = rng());
        lst[s[i]] = i;
    }
    for (int i = 1; i <= k; i++) if (lst[i]) val[lst[i]] ^= sums[i];
    int leaves = 0;
    [&](this auto dfs, int x, int p) -> array<int, 2> { // degree, XOR of remaining
        int deg = 0, cur = val[x];
        for (int y : g[x]) if (y != p) {
            auto [d, sm] = dfs(y, x);
            deg += d, cur ^= sm;
        }
        if (!cur && deg + (p > 0) == 1) ++leaves;
        return {cur ? deg : 1, cur};
    }(1, 0);
    cout << (leaves + 1) / 2 << "\n";
}