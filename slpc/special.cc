#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t


int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    auto is_connected = [&](vector<bool> qry) {
        cout << "? ";
        for (int i = 0; i < m; i++) cout << qry[i] << " ";
        cout << endl;
        bool res; cin >> res;
        return res;
    };
    auto g = vector(n + 1, vector<array<int, 2>>());
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }
    auto e_by_depth = vector(n + 1, vector<int>());
    auto v_by_depth = vector(n + 1, vector<int>());
    auto path_to = vector(n + 1, vector<int>());
    vector<bool> vis(n + 1);
    [&](this auto dfs, int x, int p, int d) -> void {
        v_by_depth[d].push_back(x);
        vis[x] = true;
        for (auto &[y, ei] : g[x]) if (!vis[y]) {
            e_by_depth[d + 1].push_back(ei);
            path_to[y] = path_to[x];
            path_to[y].push_back(ei);
            dfs(y, x, d + 1);
        }
    }(1, 0, 0);
    DBG(e_by_depth);
    DBG(path_to);
    int tgt_dep = n;
    auto query_depth = [&](int depth) {
        vector<bool> qry(m);
        for (int dep = 1; dep <= depth; dep++) {
            for (int x : e_by_depth[dep]) qry[x] = true;
        }
        return is_connected(qry);
    };
    for (int dif = (1 << 7); dif > 0; dif /= 2) {
        if (query_depth(tgt_dep - dif)) tgt_dep -= dif;
    }
    DBG(tgt_dep);
    auto &opts = v_by_depth[tgt_dep];
    assert(opts.size());
    int idx = 0;
    for (int bit = 1; bit <= (1 << 7); bit <<= 1) {
        vector<bool> qry(m);
        for (int i = 0; i < opts.size(); i++) if (bit & i) {
            for (int ei : path_to[opts[i]]) qry[ei] = 1;
        }
        if (is_connected(qry)) idx |= bit;
    }
    cout << "! " << opts[idx] << endl;
}
