#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void ac() {
    int n, k; cin >> n >> k;
    vector<int> w(n + 1), c(n + 1), bad(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i <= n; i++) cin >> c[i];
    auto elts = vector(n + 1, set<int>());
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto upd = [&](int i, int x) { if (x != c[i] && x != bad[i]) bad[i] = (!bad[i] ? x : -1); };
    int cost = 0;
    auto dfs1 = [&](this auto dfs, int x, int p) -> void {
        for (int y : g[x]) if (y != p) {
            dfs(y, x);
            if (elts[x].size() < elts[y].size()) elts[x].swap(elts[y]);
            for (int z : elts[y]) {
                if (elts[x].contains(z)) upd(x, z);
                else elts[x].insert(z);
            }
        }
        if ((bad[x] && c[x]) || bad[x] < 0) cost += w[x];
        if (c[x]) elts[x].insert(c[x]);
    };
    dfs1(1, 0);
    cout << cost << endl;
    auto dfs2 = [&](this auto dfs, int x, int p, int lst) -> void {
        if (!c[x]) {
            if (bad[x] > 0) c[x] = bad[x];
            else c[x] = lst;
        }
        for (int y : g[x]) if (y != p) dfs(y, x, c[x]);
    };
    dfs2(1, 0, 1);
    copy(++c.begin(), c.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
