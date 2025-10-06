// https://codeforces.com/contest/506/problem/D
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

int32_t main() {
    int n, m; cin >> n >> m;
    vector<vector<array<int, 2>>> by_color(m + 1);
    vector<vector<int>> g(n + 1), colors(n + 1), qs_color(m + 1);
    for (int i = m; i --> 0; ) {
        int u, v, c; cin >> u >> v >> c;
        by_color[c].push_back({u, v});
        colors[u].push_back(c);
        colors[v].push_back(c);
    }
    int q; cin >> q;
    vector<array<int, 2>> qs(q);
    map<array<int, 2>, int> mem;
    for (int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        if (pair{colors[u].size(), u} > pair{colors[v].size(), v}) swap(u, v);
        qs[i] = {u, v};
        if (!mem.contains(qs[i])) {
            for (int j : colors[u]) qs_color[j].push_back(i);
            mem[qs[i]] = i;
        }
    }
    dsu uf(n + 1);
    vector<int> ans(q), mark(n + 1);
    for (int i = 1; i <= m; i++) {
        for (auto [u, v] : by_color[i]) uf.join(u, v);
        for (int j : qs_color[i]) if (mark[j] != i) {
            mark[j] = i;
            if (uf.same(qs[j][0], qs[j][1])) ++ans[j];
        }
        for (auto [u, v] : by_color[i]) uf[u] = uf[v] = -1;
    }
    for (int i = 0; i < q; i++) cout << ans[mem[qs[i]]] << endl;
}
