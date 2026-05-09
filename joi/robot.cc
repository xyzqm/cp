#include <bits/stdc++.h>
using namespace std;

#define int int64_t
const int inf = 1e18;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    int mx = n + 2 * m + 1;
    auto g = vector(mx, vector<array<int, 3>>()); // {v, color, cost}
    auto id = vector(n + 1, map<int, int>());
    vector<int> sm(mx);
    int tot = n;
    for (int i = 0; i < m; i++) {
        int u, v, c, p; cin >> u >> v >> c >> p;
        for (int _ : {0, 1}) {
            g[u].push_back({v, c, p});
            if (!id[u].contains(c)) g[u].push_back({id[u][c] = ++tot, 0, 0});
            g[id[u][c]].push_back({v, c, p});
            sm[id[u][c]] += p;
            swap(u, v);
        }
    }
    for (int u = 1; u <= n; u++) {
        auto cur = g[u];
        for (auto &[v, c, _] : cur) if (v <= n && id[v].contains(c)) g[u].push_back({id[v][c], c, 0});
    }
    for (int u = n + 1; u <= tot; u++) for (auto &[v, _, p] : g[u]) p = sm[u] - p;
    auto dist = vector<int>(mx, inf);
    using T = array<int, 2>;
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({dist[1] = 0, 1});
    while (pq.size()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto &[v, _, p] : g[u]) if (int dv = d + p; dv < dist[v]) {
            pq.push({dist[v] = dv, v});
        }
    }
    cout << array{dist[n], (int)-1}[dist[n] == inf] << endl;
}
