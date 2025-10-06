// https://codeforces.com/contest/2155/problem/F
#include <bits/stdc++.h>
using namespace std;

struct dsu : vector<int> {
    dsu(int n) : vector(n, -1) {}
    int rep(int x) { return at(x) < 0 ? x : at(x) = rep(at(x)); }
    bool same(int x, int y) { return rep(x) == rep(y); }
    bool join(int x, int y) {
        x = rep(x), y = rep(y);
        if (x == y) return 0;
        if (at(x) > at(y)) ::swap(x, y);
        at(x) += at(y);
        at(y) = x;
        return 1;
    }
};

void ac() {
    int n, k, s, q; cin >> n >> k >> s >> q;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<vector<int>> by_color(k + 1), colors(n + 1), qs_color(k + 1);
    for (int i = 0; i < s; i++) {
        int v, x; cin >> v >> x;
        by_color[x].push_back(v);
        colors[v].push_back(x);
    }
    vector<array<int, 2>> qs(q);
    map<array<int, 2>, int> mem;
    int tot = 0;
    for (int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        if (pair{colors[u].size(), u} > pair{colors[v].size(), v}) swap(u, v);
        qs[i] = {u, v};
        if (!mem.contains(qs[i])) {
            tot += colors[u].size();
            for (int j : colors[u]) qs_color[j].push_back(i);
            mem[qs[i]] = i;
        }
    }
    vector<int> fa(n + 1);
    auto dfs = [&](this auto dfs, int x, int p) -> void {
        fa[x] = p;
        for (int y : g[x]) if (y != p) dfs(y, x);
    };
    dfs(1, 0);
    dsu uf(n + 1);
    vector<int> ans(q), mark(n + 1);
    for (int i = 1; i <= k; i++) {
        for (int j : by_color[i]) mark[j] = i;
        for (int j : by_color[i]) if (mark[fa[j]] == i) uf.join(j, fa[j]);
        for (int j : qs_color[i]) if (uf.same(qs[j][0], qs[j][1])) ++ans[j];
        for (int j : by_color[i]) uf[j] = -1;
    }
    for (int i = 0; i < q; i++) cout << ans[mem[qs[i]]] << " ";
    cout << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
