#include <bits/stdc++.h>
using namespace std;

using basis = vector<int>;
void operator+=(basis &b, int x) {
    for (int y : b) x = min(x, y ^ x);
    if (x) b.push_back(x);
}
void operator+=(basis &a, basis b) { for (int x : b) a += x; }
int mx(basis b) {
    int r = 0;
    for (int x : b) r = max(r, r ^ x);
    return r;
}

void ac() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    a.insert(a.begin(), 0);
    auto g = vector(++n, vector<int>());
    for (int i = 2; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto b = vector(n, vector<int>());
    auto pre = b, suf = b, rt = b;
    vector<int> t(n), sz(n, 1);
    int tt = 0;
    auto dfs = [&](this auto dfs, int x, int p) -> void {
        if (p) g[x].erase(ranges::find(g[x], p));
        b[x] += a[x];
        t[x] = tt++;
        for (auto it = g[x].begin(); it != g[x].end(); it++) {
            dfs(*it, x);
            sz[x] += sz[*it];
            b[x] += b[*it];
            if (it != g[x].begin()) pre[*it] += pre[*prev(it)];
        }
        if (g[x].size()) for (auto it = ++g[x].rbegin(); it != g[x].rend(); it++) suf[*it] += suf[*prev(it)];
        pre[x] = suf[x] = b[x];
    };
    dfs(1, 0);
    auto exclude = [&](int x, int c) {
        assert(t[x] <= t[c] && t[c] < t[x] + sz[x]);
        auto it = ranges::lower_bound(g[x], t[c], [&](int i, int tt) { return t[i] + sz[i] <= tt; });
        // cout << x << " " << c << " " << *it << endl;
        assert(it != g[x].end());
        basis b;
        if (it != g[x].begin()) b += pre[*prev(it)];
        if (next(it) != g[x].end()) b += suf[*next(it)];
        return b;

    };
    auto down = [&](this auto down, int x) -> void {
        rt[x] += a[x];
        for (int y : g[x]) {
            rt[y] += exclude(x, y);
            rt[y] += rt[x];
            down(y);
        }
    };
    down(1);
    int q; cin >> q;
    while (q--) {
        int r, v; cin >> r >> v;
        basis bb;
        if (t[r] < t[v] || t[r] >= t[v] + sz[v]) bb = b[v];
        else {
            bb = rt[v];
            if (v != r) bb += exclude(v, r);
            else bb += b[r];
        }
        cout << mx(bb) << endl;
    }
}

int main() {
    int t; cin >> t;
    while (t--) ac();
}
