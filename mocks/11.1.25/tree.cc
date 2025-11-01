#include <bits/stdc++.h>
using namespace std;

const int K = 20;

int main() {
    int n; cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // euler tour
    vector<int> d(n + 1), et, idx(n + 1);
    auto dfs = [&](auto &&f, int x, int p) -> void {
        d[x] = d[p] + 1;
        idx[x] = et.size();
        et.push_back(x);
        for (int y : g[x]) if (y != p) {
            f(f, y, x);
            et.push_back(x);
        }
    };
    dfs(dfs, 1, 0);

    // sparse table LCA
    auto mn = [&](int i, int j) { return d[i] < d[j] ? i : j; };
    auto smin = [&] (int &i, int j) { i = mn(i, j); };
    array<vector<int>, K> sp;
    sp[0] = et;
    for (int k = 0; k + 1 < K; k++) {
        sp[k + 1] = sp[k];
        for (int i = 0, x = 1 << k; x < sp[k].size(); i++, x++) smin(sp[k + 1][i], sp[k][x]);
    };
    auto lca = [&](int u, int v) {
        int l = min(idx[u], idx[v]), r = max(idx[u], idx[v]);
        int k = __lg(++r - l);
        return mn(sp[k][l], sp[k][r - (1 << k)]);
    };
    auto len = [&](int u, int v) { return d[u] + d[v] - 2 * d[lca(u, v)]; };

    // input colors and compute roots for each
    int k; cin >> k;
    vector<vector<pair<int, int>>> color(k + 1);
    vector<int> rt(k + 1);
    for (int i = 1; i <= k; i++) {
        int c, x; cin >> c;
        while (c--) {
            cin >> x;
            if (!rt[i]) rt[i] = x;
            else rt[i] = lca(rt[i], x);
            color[i].push_back({idx[x], x});
        }
        sort(color[i].begin(), color[i].end());
    }

    int q; cin >> q;
    vector<vector<int>> qs(q), qq(n + 1);
    for (int i = 0; i < q; i++) {
        int x, s; cin >> x >> s;
        qs[i].resize(s);
        int RT = 0, res = n + 1;
        for (int &c : qs[i]) {
            cin >> c;
            if (!RT) RT = rt[c];
            else RT = lca(RT, rt[c]);
        }
        auto upd = [&](int y) {
            y = lca(y, x);
            if (lca(y, RT) == RT) res = min(res, len(x, y));
            else res = min(res, len(x, RT));
        };
        for (int c : qs[i]) {
            auto it = lower_bound(color[c].begin(), color[c].end(), pair{idx[x], x});
            if (it != color[c].end()) upd(it->second);
            if (it != color[c].begin()) upd(prev(it)->second);
        }
        cout << res << endl;
    }
}
