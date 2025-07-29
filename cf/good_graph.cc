// https://codeforces.com/contest/1555/problem/F
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 1;
const int K = 20;

int fa[N], sz[N];
int rt(int x) { return x == fa[x] ? x : (fa[x] = rt(fa[x])); }
bool join(int u, int v) {
    u = rt(u), v = rt(v);
    if (u == v) return false;
    if (sz[u] < sz[v]) swap(u, v);
    fa[v] = u, sz[u] += sz[v];
    return true;
}

vector<array<int, 2>> g[N];

int j[N][K], w[N], d[N], v[N], id[N], s[N], t = 0;

int dfs(int x) {
    v[x] = 1, id[x] = t++;
    for (int k = 0; k + 1 < K; k++) j[x][k + 1] = j[j[x][k]][k];
    for (auto [y, w] : g[x]) if (!v[y]) {
        ::w[y] = ::w[x] ^ w;
        d[y] = d[x] + 1;
        j[y][0] = x;
        s[x] += dfs(y);
    }
    return ++s[x];
}

int bit[N];
// sum from [0, x]
int query(int x) {
    int r = 0;
    for (++x; x; x -= x & -x) r += bit[x];
    return r;
}
// increment i
void upd(int i, int v) { for (++i; i < N; i += i & -i) bit[i] += v; }
void inc(int l, int r) { upd(l, 1); upd(r, -1); }

int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    for (int k = 0; k < K; k++) if ((d[u] - d[v]) >> k & 1) u = j[u][k];
    for (int k = K; k --> 0; ) if (j[u][k] != j[v][k]) u = j[u][k], v = j[v][k];
    return u == v ? u : j[u][0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<array<int, 4>> bad;
    iota(fa, fa + N, 0);
    fill(sz, sz + N, 1);
    for (int i = 0; i < m; i++) {
        int u, v, x; cin >> u >> v >> x;
        if (join(u, v)) {
            g[u].push_back({v, x});
            g[v].push_back({u, x});
        }
        else bad.push_back({i, u, v, x});
    }
    for (int i = 1; i <= n; i++) if (!v[i]) dfs(i);
    vector<int> r(m, true);
    for (auto &[i, u, v, x] : bad) {
        if (w[u] ^ w[v] ^ x != 1) r[i] = false;
        else {
            int l = lca(u, v);
            if (query(id[u]) + query(id[v]) - 2 * query(id[l]) > 0) r[i] = false;
            else {
                for (; u != l; u = j[u][0]) inc(id[u], id[u] + s[u]);
                for (; v != l; v = j[v][0]) inc(id[v], id[v] + s[v]);
            }
        }
    }
    for (int i = 0; i < m; i++) cout << vector{"NO", "YES"}[r[i]] << endl;
}
