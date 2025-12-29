#include <bits/stdc++.h>
using namespace std;

struct dsu : vector<int> {
    dsu(int n) : vector(n, -1) {}
    int rep(int x) { return at(x) < 0 ? x : at(x) = rep(at(x)); }
    bool same(int x, int y) { return rep(x) == rep(y); }
    int join(int x, int y) {
        x = rep(x), y = rep(y);
        if (x == y) return 0;
        if (at(x) > at(y)) ::swap(x, y);
        at(x) += at(y);
        at(y) = x;
        return x;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, q, tid; cin >> n >> m >> q >> tid;
    vector<array<int, 2>> e(m + 1);
    for (int i = 1; i <= m; i++) cin >> e[i][0] >> e[i][1];
    vector<array<int, 3>> qs(q);
    vector<bool> del(m + 1);
    for (auto &[t, u, v] : qs) {
        cin >> t >> u;
        if (t > 1) cin >> v;
        else del[u] = true;
    }
    dsu conn(n + 1);
    reverse(qs.begin(), qs.end());
    vector<bool> tree(m + 1);
    auto g = vector(n + 1, vector<int>());
    auto add_edge = [&](int i) {
        tree[i] = conn.join(e[i][0], e[i][1]);
        if (tree[i]) for (int t : {0, 1}) g[e[i][t]].push_back(e[i][t ^ 1]);
    };
    for (int i = 1; i <= m; i++) if (!del[i]) add_edge(i);
    for (auto &[t, u, _] : qs) if (t == 1) add_edge(u);
    vector<int> par(n + 1), dep(n + 1);
    auto dfs = [&](auto &&f, int x, int p) -> void {
        par[x] = p;
        dep[x] = dep[p] + 1;
        for (int y : g[x]) if (y != p) f(f, y, x);
    };
    for (int i = 1; i <= n; i++) if (!par[i]) dfs(dfs, i, i);
    dsu blc(n + 1);
    vector<int> rt(n + 1);
    iota(rt.begin(), rt.end(), 0);
    string ans = "";
    auto add_cycle = [&](int u) {
        if (!tree[u]) {
            auto [x, y] = e[u];
            while (!blc.same(x, y)) {
                x = rt[blc.rep(x)], y = rt[blc.rep(y)];
                if (dep[x] > dep[y]) swap(x, y);
                int z = rt[blc.rep(par[y])];
                rt[blc.join(y, par[y])] = z;
            }
        }
    };
    for (int i = 1; i <= m; i++) if (!del[i]) add_cycle(i);
    for (auto &[t, u, v] : qs) {
        if (t == 1) add_cycle(u);
        else {
            ans += array{"\nON", "\nSEY"}[blc.same(u, v)];
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
}
