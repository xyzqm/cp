#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    auto g = vector(n + 1, vector<pair<int, array<int, 2>>>());
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        int c, d; cin >> c >> d;
        g[u].push_back({v, {c, d}});
        g[v].push_back({u, {d, c}});
    }
    vector<int> away(n + 1);
    away[1] = [&](this auto &&dfs, int x, int p) -> int {
        int res = 0;
        for (auto [y, w] : g[x]) if (y != p) res += w[0] + dfs(y, x);
        return res;
    }(1, 0);
    [&](this auto &&dfs, int x, int p) -> void {
        for (auto [y, w] : g[x]) if (y != p) {
            away[y] = away[x] + w[1] - w[0];
            dfs(y, x);
        }
    }(1, 0);
    DBG(away);
    vector<int> ans(n + 1, (int)1e18);
    vector<bool> removed(n + 1);
    vector<int> height(n + 1);

    auto get_dists = [&](this auto &&dfs, int x, int p) -> void {
        height[x] = 0;
        array<int, 2> mx = {0, -1};
        for (int i = 0; i < (int)g[x].size(); i++) {
            auto [y, w] = g[x][i];
            if (y != p && !removed[y]) {
                dfs(y, x);
                mx = max(mx, {height[y] + w[0], i});
            }
        }
        if (mx[0]) height[x] = mx[0], swap(g[x][0], g[x][mx[1]]);
    };

    auto greedy = [&](this auto &&dfs, int x, int p, int wp, int lb, vector<array<int, 2>> &v) -> void {
        for (auto [y, w] : g[x]) if (y != p && !removed[y]) {
            dfs(y, x, wp + w[0], lb, v);
            wp = 0;
        }
        if (wp) v.push_back({wp, lb}); // leaf
    };

    vector<int> sz(n + 1);
    auto get_sz = [&](this auto &&dfs, int x, int p) -> int {
        sz[x] = 1;
        for (auto [y, w] : g[x]) if (y != p && !removed[y]) sz[x] += dfs(y, x);
        return sz[x];
    };

    [&](this auto &&dfs, int x, int p, int comp_size) -> void {
        for (auto [y, w] : g[x]) if (y != p && !removed[y]) {
            if (sz[y] * 2 > comp_size) return dfs(y, x, comp_size);
        }
        get_dists(x, 0);
        vector<array<int, 2>> vals;
        for (auto [y, w] : g[x]) if (!removed[y]) {
            greedy(y, x, w[0], y, vals);
        }

        ranges::sort(vals);
        ans[1] = min(ans[1], away[x]);
        for (int i = vals.size(); i --> 0; ) if (vals[i][1] != vals.back()[1]) {
            vals.insert(vals.end() - 1, vals[i]);
            vals.erase(vals.begin() + i);
            break;
        }
        for (int i = vals.size(), cur = away[x], cnt = 1; i --> 0; cnt++) {
            cur -= vals[i][0];
            ans[max(cnt, (int)2)] = min(ans[max(cnt, (int)2)], cur);
        }
        removed[x] = true;
        for (auto [y, w] : g[x]) if (!removed[y]) dfs(y, x, get_sz(y, x));
    }(1, 0, get_sz(1, 0));

    for (int i = 2; i <= n; i++) ans[i] = min(ans[i], ans[i - 1]);

    DBG(ans);
    int q; cin >> q;
    while (q--) {
        int e; cin >> e;
        cout << ans[e] << "\n";
    }
}
