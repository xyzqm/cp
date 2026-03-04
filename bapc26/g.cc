#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int K = 20;

struct bit : vector<int> {
    bit(int n) : vector(n + 1) {}
    void upd(int i, int x) { // increment index i by x
        for (++i; i < size(); i += i & -i) at(i) += x;
    }
    int query(int r) { // sum [0, r]
        int val = 0;
        for (++r; r; r -= r & -r) val += at(r);
        return val;
    }
    int query(int l, int r) { return query(r) - query(l); }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto jmp = vector(n + 1, array<int, K>());
    vector<int> dep(n + 1), tin(n + 1), sz(n + 1); int t = 0;
    auto dfs = [&](auto &&f, int x, int p) -> int {
        tin[x] = t++;
        dep[x] = dep[jmp[x][0] = p] + 1;
        for (int k = 0; k + 1 < K; k++) jmp[x][k + 1] = jmp[jmp[x][k]][k];
        for (auto y : g[x]) if (y != p) {
            sz[x] += f(f, y, x);
        }
        return ++sz[x];
    };
    dfs(dfs, 1, 0);
    DBG(dep);
    DBG(tin);
    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        if (dep[u] > dep[v]) for (int k = K; k --> 0; ) if ((dep[u] - dep[v]) >> k & 1) u = jmp[u][k];
        if (u == v) return u;
        for (int k = K; k --> 0; ) if (jmp[u][k] != jmp[v][k]) u = jmp[u][k], v = jmp[v][k];
        return jmp[u][0];
    };
    DBG(lca(1, 3));
    int q; cin >> q;
    vector<array<int, 5>> qs(q);
    int q2 = 0;
    for (auto &[tim, typ, a, b, idx] : qs) {
        cin >> typ >> tim >> a >> b;
        if (typ == 2) idx = q2++;
    }
    sort(qs.begin(), qs.end());
    DBG(qs);
    vector<int> res(q2);
    bit sm(n), cnt(n);
    auto path_query = [&](bit &b, int u, int v) {
        int res = b.query(tin[u]) + b.query(tin[v]) - b.query(tin[lca(u, v)]);
        int par_l = jmp[lca(u, v)][0];
        if (par_l) res -= b.query(tin[par_l]);
        DBG(u);
        DBG(v);
        DBG(res);
        return res;
    };
    DBG(sz);
    for (auto &[tim, typ, a, b, idx] : qs) {
        if (typ == 1) {
            sm.upd(tin[a], b + tim);
            sm.upd(tin[a] + sz[a], -b - tim);
            cnt.upd(tin[a], 1);
            cnt.upd(tin[a] + sz[a], -1);
        }
        if (typ == 2) {
            res[idx] = path_query(sm, a, b) - path_query(cnt, a, b) * tim;
        }
    }
    DBG(res);
    for (int x : res) cout << x << "\n";
}
