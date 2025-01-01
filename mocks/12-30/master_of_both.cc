// https://qoj.ac/contest/1885/problem/9918
#include <bits/stdc++.h>
using namespace std;
#define loop(i, n) for (int i = 0; i < n; i++)
#define upd(a, b) a = min(a, b)
#define int int64_t

const int inf = 1e18;

// min/+ matrix operations
using M = array<array<int, 2>, 2>;
using V = array<int, 2>;
ostream& operator<<(ostream &os, M mat) {
    os << "|" << mat[0][0] << " " << mat[0][1] << "|\n";
    os << "|" << mat[1][0] << " " << mat[1][1] << "|\n";
    return os;
}
M operator*(const M &a, const M &b) {
    M c;
    loop(i, 2) loop(j, 2) {
        c[i][j] = inf;
        loop(k, 2) upd(c[i][j], a[i][k] + b[k][j]);
    }
    return c;
}

// sparse segment tree + segtree merging
const int N = 5e5 + 1;
const int SGT = 40 * N;
int lc[SGT], rc[SGT], c[SGT], id = 1;
M v[SGT], iden = {{{0, inf}, {inf, 0}}};

void pull(int p) {
    v[p] = v[lc[p]] * v[rc[p]];
    c[p] = c[lc[p]] + c[rc[p]];
}

int edit(int i, M x, int p, int l = 0, int r = N) {
    if (!p) p = id++;
    if (r - l == 1) {
        v[p] = x;
        c[p] = x != iden;
    }
    else {
        int m = (l + r) >> 1;
        if (i < m) lc[p] = edit(i, x, lc[p], l, m);
        else rc[p] = edit(i, x, rc[p], m, r);
        pull(p);
    }
    return p;
}

int merge(int p1, int p2) {
    if (!p1) return p2;
    if (!p2) return p1;
    lc[p1] = merge(lc[p1], lc[p2]);
    rc[p1] = merge(rc[p1], rc[p2]);
    if (lc[p1] || rc[p1]) pull(p1);
    else assert(v[p1] == v[p2] && c[p1] == c[p2]);
    return p1;
}

int dmg(M v) { return min({v[0][0], v[0][1], v[1][0], v[1][1]}); }
struct R { M v; int c, lb; };
R walk(int rb, int h, int p, M v = iden, int c = 0, int l = 0, int r = N) {
    int m = (l + r) >> 1;
    if (!p) return {v, c, l};
    if (r <= rb) {
        if (dmg(::v[p] * v) < h) return {::v[p] * v, ::c[p] + c, l};
        if (r - l == 1) return {v, c, r};
    }
    if (m < rb) {
        auto ret = walk(rb, h, rc[p], v, c, m, r);
        if (ret.lb > m) return ret;
        else v = ret.v, c = ret.c;
    }
    return walk(rb, h, lc[p], v, c, l, m);
}

// lca
const int K = 20;
int n, fa[N][K], d[N];
vector<int> g[N];

void dfs(int x, int p) {
    fa[x][0] = p, d[x] = d[p] + 1;
    loop(k, K - 1) fa[x][k + 1] = fa[fa[x][k]][k];
    for (int y : g[x]) if (y != p) dfs(y, x);
}

int lca(int x, int y) {
    if (d[x] < d[y]) swap(x, y);
    for (int k = K; k --> 0; ) if ((d[x] - d[y]) >> k & 1) x = fa[x][k];
    if (x == y) return x;
    for (int k = K; k --> 0; ) if (fa[x][k] != fa[y][k]) x = fa[x][k], y = fa[y][k];
    return fa[x][0];
}

// solve
struct Q { int t, h; };
M mat[N];
vector<Q> q[N];
vector<int> add[N], rem[N];
int r[N], sgt[N];

void ac(int x, int p) {
    for (int y : g[x]) if (y != p) {
        ac(y, x);
        sgt[x] = merge(sgt[x], sgt[y]);
    }
    for (int i : add[x]) sgt[x] = edit(i, mat[i], sgt[x]);
    for (auto [t, h] : q[x]) {
        auto [mat, c, lb] = walk(t, h, sgt[x]);
        r[t] = c;
    }
    for (int i : rem[x]) sgt[x] = edit(i, iden, sgt[x]);
}

int32_t main() {
    int q; cin >> n >> q;
    loop(_, n - 1) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    loop(i, q) {
        char t; cin >> t;
        if (t == 'A') {
            int x, y, z; cin >> x >> y >> z;
            mat[i] = {{{2 * z, z}, {2 * z, inf}}};
            add[x].push_back(i);
            add[y].push_back(i);
            rem[lca(x, y)].push_back(i);
        }
        else {
           int x, h; cin >> x >> h;
           ::q[x].push_back({i, 2 * h});
        }
    }
    fill(r, r + q, -1);
    fill(v, v + SGT, iden);
    ac(1, 0);
    loop(i, q) if (r[i] != -1) cout << r[i] << endl;
}
