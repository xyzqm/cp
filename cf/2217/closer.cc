#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void ac() {
    int n; cin >> n;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];
    // DBG(w);
    n *= 2;
    vector<int> l(n + 1);
    for (int i = 1; i <= n; i++) cin >> l[i];
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> fa(n + 1);
    // run a dfs
    [&](this auto &&self, int x) -> void {
        for (int y : g[x]) {
            g[y].erase(ranges::find(g[y], fa[y] = x));
            self(y);
        }
    }(1);
    vector<int> dp(n + 1); // dp[i] => max if don't swap i
    vector<int> swp(n + 1); // max if swap i with parent
    auto benefit = [&](int u, int v) { return (l[u] == l[v]) * w[l[u]]; };
    auto get_best = [&](int u, int par) { // WARNING: takes O(deg[u]) time
        int mx = dp[u] + benefit(u, par);
        for (int v : g[u]) mx = max(mx, swp[v] + benefit(v, par));
        return mx;
    };
    vector<int> opt(n + 1);
    auto mp = vector(n + 1, vector<int>());
    // run DP
    [&](this auto &&self, int x) -> void {
        int baseline = 0;
        auto ins = [&](int u) { mp[l[u]].push_back(u); };
        auto del = [&](int u) { mp[l[u]].erase(ranges::find(mp[l[u]],u)); };
        for (int y : g[x]) {
            self(y);
            dp[x] += get_best(y, x);
            baseline += (opt[y] = get_best(y, 0));
        }
        for (int y : g[x]) {
            ins(y);
            for (int z : g[y]) ins(z);
        }
        for (int y : g[x]) { // consider swapping with y
            del(y);
            for (int z : g[y]) del(z);
            // first, consider contribution of subtree of y
            for (int z : g[y]) swp[y] += get_best(z, x);
            swp[y] += baseline - opt[y];
            if (mp[l[y]].size()) {
                assert(mp[l[y]].size() == 1);
                int z = mp[l[y]][0];
                assert(l[z] == l[y]);
                if (fa[z] == x) swp[y] += max((int)0, w[l[y]] + dp[z] - opt[z]);
                else swp[y] += max((int)0, swp[z] + w[l[y]] - opt[fa[z]]);
            }
            ins(y);
            for (int z : g[y]) ins(z);
        }
        for (int y : g[x]) {
            del(y);
            for (int z : g[y]) del(z);
        }
    }(1);
    cout << max(*ranges::max_element(dp), *ranges::max_element(swp)) << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
