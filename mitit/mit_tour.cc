#include <bits/stdc++.h>
#define int int64_t
using namespace std;

const int N = 2e5 + 1;
const int K = 20;
const int inf = 1e18;

struct E { int v, w; };
vector<E> g[N];
int n, ml = 0, p[N], d[N], t[N], r[N], s[N], l[N], cp[N], dp[N], opt[N][2];
vector<int> sp[K], lv[N];

int md(int i, int j) { return d[i] < d[j] ? i : j; }

void dfs(int x) {
    lv[l[x] = l[p[x]] + 1].push_back(x);
    ml = max(ml, l[x]);
    for (auto [y, w] : g[x]) {
        t[x] = sp[0].size();
        sp[0].push_back(x);
        if (y != p[x]) {
            d[y] = d[p[y] = x] + w;
            dfs(y);
        }
    }
}

int sz(int x, int p) {
    s[x] = 0;
    for (auto [y, _] : g[x]) if (y != p && !r[y]) s[x] += sz(y, x);
    return ++s[x];
}
int cdc(int x, int p, int n) {
    for (auto [y, _] : g[x]) if (y != p && !r[y]) {
        if (s[y] > n / 2) return cdc(y, x, n);
    }
    r[x] = 1;
    for (auto [y, _] : g[x]) if (!r[y]) {
        cp[cdc(y, x, sz(y, 0))] = x;
    }
    return x;
}

int lca(int u, int v) {
    u = t[u], v = t[v];
    if (u > v) swap(u, v);
    int k = log2(++v - u);
    return md(sp[k][u], sp[k][v - (1 << k)]);
}
int dist(int u, int v) { return d[u] + d[v] - 2 * d[lca(u, v)]; }

int cost(int x, int cp) { return dp[x] + dist(x, cp); }
// update centroid parent cp with x
void upd(int x, int cp) {
    for (int t : {0, 1}) if (cost(x, cp) < cost(opt[cp][t], cp)) {
        if (!t && p[x] != p[opt[cp][0]]) opt[cp][1] = opt[cp][0];
        if (!t || p[x] != p[opt[cp][0]]) return (void)(opt[cp][t] = x);
    }
}

int32_t main() {
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    p[0] = l[0] = -1; dfs(1);
    for (int k = 1; k < K; k++) {
        sp[k] = sp[k - 1];
        for (int i = 0, d = 1 << (k - 1); i + d < sp[k].size(); i++) sp[k][i] = md(sp[k][i], sp[k - 1][i + d]);
    }
    cdc(1, 0, sz(1, 0));
    fill(dp, dp + N, inf);
    vector<int> buf;
    for (int x : lv[ml]) {
        dp[x] = 0;
        for (int j = x; j; j = cp[j]) {
            upd(x, j);
            buf.push_back(j);
        }
    }
    for (int l = ml; l --> 0; ) {
        for (int x : lv[l]) {
            for (int j = x; j; j = cp[j]) {
                dp[x] = min(dp[x], dist(x, j) + cost(opt[j][l && p[opt[j][0]] == x], j));
            }
        }
        for (int x : buf) opt[x][0] = opt[x][1] = 0;
        buf.clear();
        for (int x : lv[l]) {
            for (int j = x; j; j = cp[j]) {
                upd(x, j);
                buf.push_back(j);
            }
        }

    }
    cout << dp[1] << endl;
}
