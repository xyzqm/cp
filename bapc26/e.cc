#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int inf = 1e18;

void ac() {
    int n, m; cin >> n >> m;
    int a, b, u, v, w; cin >> a >> b >> u >> v >> w;
    --a, --b, --u, --v;
    auto input_mat = [&]() {
        auto mat = vector(n, vector<int>(m));
        for (auto &v : mat) for (int &x : v) cin >> x;
        return mat;
    };
    auto d = input_mat(), h = input_mat();
    DBG(d);
    DBG(h);
    auto hsh = [&](int r, int c, int mn_h) {
        return (r * m + c) * 11 + mn_h;
    };
    int mx = n * m * 11;
    auto g = vector(mx, vector<array<int, 2>>());
    auto add_edge = [&](int u, int v, int w) {
        g[u].push_back({v, w});
        // g[v].push_back({u, w});
    };
    for (int r = 0; r < n; r++) for (int c = 0; c < m; c++) for (int mn_h = 0; mn_h <= 10; mn_h++) {
        for (auto [dr, dc] : array<array<int, 2>, 4>{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}}) {
            int nr = r + dr, nc = c + dc;
            if (0 <= nr && nr < n && 0 <= nc && nc < m) {
                if (mn_h) add_edge(hsh(r, c, mn_h), hsh(nr, nc, min(mn_h, h[nr][nc])), h[r][c]);
                else add_edge(hsh(r, c, mn_h), hsh(nr, nc, min(mn_h, h[nr][nc])), d[nr][nc] ? 1 : h[nr][nc]);
            }
        }
    }
    auto ss_sp = [&](int u) {
        vector<int> dist(mx, inf);
        using T = array<int, 2>;
        priority_queue<T, vector<T>, greater<T>> pq;
        pq.push({dist[u] = 0, u});
        while (pq.size()) {
            auto [d, u] = pq.top(); pq.pop();
            if (dist[u] != d) continue;
            for (auto &[v, w] : g[u]) if (d + w < dist[v]) {
                pq.push({dist[v] = d + w, v});
            }
        }
        return dist;
    };
    auto dist_src = ss_sp(hsh(a, b, 0));
    #ifndef ONLINE_JUDGE
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cout << dist_src[hsh(i, j, 0)] << " \n"[j == m - 1];
    #endif
    auto dist_sink = ss_sp(hsh(u, v, h[u][v]));
    int res = inf;
    for (int r = 0; r < n; r++) for (int c = 0; c < m; c++) for (int min_h = 1; min_h <= 10; min_h++) {
        int swim = min(w, d[r][c] - 1);
        res = min(
            res,
            dist_src[hsh(r, c, 0)] + dist_sink[hsh(r, c, min_h)] // horizontal distance
            + swim + (w - swim) * min_h
        );
    }
    cout << res << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
