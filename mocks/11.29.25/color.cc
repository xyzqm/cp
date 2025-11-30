#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void ac() {
    int n, q; cin >> n >> q;
    vector<int> t(n + 1), b(n + 1), in(n + 1);
    vector<vector<int>> rg(n + 1);
    for (int i = 1; i <= n; i++) cin >> t[i];
    for (int i = 1; i <= n; i++) cin >> b[i], ++in[b[i]], rg[b[i]].push_back(i);
    vector<bool> cyc(n + 1, true); // figure out which are cycle nodes
    vector<int> stk;
    for (int i = 1; i <= n; i++) if (!in[i]) stk.push_back(i);
    while (stk.size()) {
        int x = stk.back(); stk.pop_back();
        cyc[x] = false;
        if (--in[b[x]] == 0) stk.push_back(b[x]);
    }
    vector<vector<array<int, 3>>> qs(n + 1); // {cnt, type, idx}
    for (int i = 0; i < q; i++) {
        int u, k, t; cin >> u >> k >> t;
        qs[u].push_back({k, t, i});
    }
    vector<int> dep(n + 1), res(q);
    vector<vector<int>> colors(n + 1);
    auto dfs = [&](auto &&f, int x, int rt, int p) -> void {
        dep[x] = dep[p] + 1;
        if (x != rt) {
            colors[t[x]].push_back(x);
            while (qs[x].size()) {
                auto [k, t, idx] = qs[x].back(); qs[x].pop_back();
                if (k <= colors[t].size()) res[idx] = dep[x] - dep[*(colors[t].end() - k)];
                else res[idx] += dep[x] - dep[rt], qs[rt].push_back({k - (int)colors[t].size(), t, idx});
            }
        }
        for (int y : rg[x]) if (y != p && !cyc[y]) f(f, y, rt, x);
        if (x != rt) {
            assert(colors[t[x]].back() == x);
            colors[t[x]].pop_back();
        }
    };
    for (int i = 1; i <= n; i++) if (cyc[i]) dfs(dfs, i, i, 0);
    vector<bool> vis(n + 1);
    colors.assign(n + 1, vector<int>());
    vector<int> id(n + 1);
    for (int i = 1; i <= n; i++) if (cyc[i] && !vis[i]) {
        vector<int> act, cur;
        for (int cnt = 0; !vis[i]; vis[i] = true, id[i] = cnt++, i = b[i]) colors[t[i]].push_back(i), act.push_back(t[i]), cur.push_back(i);
        for (int x : cur) for (auto [k, t, idx] : qs[x]) {
            if (!colors[t].size()) res[idx] = -2;
            else {
                int cycs = (k + colors[t].size() - 1) / colors[t].size() - 1; // ceil - 1
                k -= cycs * colors[t].size();
                assert(k);
                res[idx] += cycs * cur.size();
                auto nx = lower_bound(colors[t].begin(), colors[t].end(), x, [&](int i, int j) { return id[i] < id[j]; } );
                int rem = colors[t].end() - nx;
                if (rem >= k) {
                    int dist = id[*(nx + k - 1)] - id[x];
                    res[idx] += dist;
                }
                else {
                    int dist = id[colors[t][k - rem - 1]] + cur.size() - id[x];
                    res[idx] += dist;
                }
            }
        }
        for (int c : act) colors[c].clear();
    }
    for (int x : res) cout << x + 1 << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
