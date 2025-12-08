#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void mg(vector<int>& a, vector<int>& b) {
    a[0] += b[0];
    int sz = a.size();
    a.insert(a.end(), b.begin() + 1, b.end());
    inplace_merge(a.begin() + 1, a.begin() + sz, a.end());
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<array<int, 2>>> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    auto dfs = [&](auto &&f, int x, int p) -> vector<int> {
        vector<int> cur = {0};
        for (auto &[y, w] : g[x]) if (y != p) {
            auto v = f(f, y, x);
            v[0] += 2 * w * (v.size() - 1);
            v[1] -= 2 * w * (v.size() - 1);
            mg(cur, v);
        }
        if (cur.size() == 1) cur.push_back(0);
        return cur;
    };
    auto v = dfs(dfs, 1, 0);
    partial_sum(v.begin(), v.end(), v.begin());
    v.resize(n + 1);
    for (int i = 1; i <= n; i++) cout << v[i] << " \n"[i == n];
}
