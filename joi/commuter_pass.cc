#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int inf = 1e18;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    int s, t, u, v; cin >> s >> t >> u >> v;
    auto g = vector(n + 1, vector<array<int, 2>>());
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        for (auto _ : array{0, 1}) {
            g[u].push_back({v, w});
            swap(u, v);
        }
    }
    auto djikstra = [&](int s, vector<int> aux = {}) {
        aux.resize(n + 1);
        vector<array<int, 2>> d(n + 1);
        ranges::fill(d, array{inf, inf});
        using T = pair<array<int, 2>, int>;
        priority_queue<T, vector<T>, greater<T>> pq;
        pq.push({d[s] = {0, aux[s]}, s});
        while (pq.size()) {
            auto [du, u] = pq.top(); pq.pop();
            if (du != d[u]) continue;
            du[1] = min(du[1], aux[u]), d[u] = du;
            for (auto &[v, w] : g[u]) if (array nx = {du[0] + w, du[1]}; nx < d[v]) {
                pq.push({d[v] = nx, v});
            }
        }
        return d;
    };
    auto filter = views::transform([](auto a) { return a[0]; }) | ranges::to<vector>();
    auto aux = array{djikstra(u) | filter, djikstra(v) | filter};
    int ans = aux[0][v];
    for (int i : {0, 1}) {
        auto ds = djikstra(s, aux[i]), dt = djikstra(t, aux[!i]);
        for (int u = 1; u <= n; u++) if (ds[u][0] + dt[u][0] == ds[t][0]) {
            ans = min(ans, ds[u][1] + dt[u][1]);
        }
    }
    cout << ans << "\n";
}
