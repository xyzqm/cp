#include <bits/stdc++.h>
using namespace std;

#define int int64_t

using pt = array<int, 4>;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<pt> pts(n);
    for (int idx = 1; auto &[x, y, t, i] : pts) {
        cin >> x >> y >> t;
        i = idx++;
    }
    sort(pts.begin(), pts.end());
    map<int, pt> ys;
    vector<array<vector<int>, 2>> g(n + 1);
    vector<pt> col;
    auto join = [&](int u, int v, int t) {
        g[u][t].push_back(v);
        g[v][t].push_back(u);
    };
    for (auto pt : pts) {
        auto [x, y, t, i] = pt;
        if (col.size() && x != col.back()[0]) col.clear();
        // add vertical edges
        if (col.size() && col.back()[2] == t) join(i, col.back()[3], 1);
        // add horizontal edges
        if (ys.contains(y) && ys[y][2] == t) join(i, ys[y][3], 0);
        col.push_back(pt);
        ys[y] = pt;
    }
    vector<array<int, 2>> match;
    vector<bool> vis(n + 1);
    auto dfs = [&](this auto dfs, int x, int t) -> int {
        vis[x] = true;
        array<int, 2> rem{};
        for (int t : {0, 1}) {
            assert(g[t].size() <= 2);
            vector<int> res;
            for (int &y : g[x][t]) if (!vis[y]) {
                if (int u = dfs(y, t); u) res.push_back(u);
            }
            if (res.size() == 2) match.push_back({res[0], res[1]});
            else if (res.size() == 1) rem[t] = res[0];
        }
        if (rem[0] + rem[1] == 0) return x;
        else if (rem[0] && rem[1]) {
            match.push_back({x, rem[t ^ 1]});
            return rem[t];
        }
        else {
            match.push_back({x, rem[0] + rem[1]});
            return 0;
        }
    };
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        if (dfs(i, 0)) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    for (auto &[u, v] : match) {
        cout << u << " " << v << "\n";
    }
}
