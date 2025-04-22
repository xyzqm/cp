#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define loop(i, n) for (int i = 0; i < n; i++)

const int M = 1e9 + 7;
const int N = 2e5 + 1;
const int K = 20;

struct mint {
    int v;
    mint() {}
    mint(int v) : v((v % M + M) % M) {}
    operator int() { return v; }
    mint& operator+=(const mint& o) { v = (v + o.v) % M; return *this; }
    mint& operator*=(const mint& o) { v = (v * o.v) % M; return *this; }
    friend istream& operator>>(istream& s, mint& v) { s >> v.v; return s; }
    friend ostream& operator<<(ostream& s, const mint& v) { s << v.v; return s; }
};

using T = mint;
using mat = array<array<T, 2>, 2>;
using vec = array<T, 2>;
mat operator*(mat a, mat b) {
    mat c = {{{0, 0}, {0, 0}}};
    loop(i, 2) loop(j, 2) loop(k, 2) c[i][j] += a[i][k] * b[k][j];
    return c;
}

mat mtx[N][K], dp[N];
int n, fa[N][K], id[N], d[N], cnt = 0;
vector<bool> in;
vector<int> v, g[N];

void dfs(int x) {
    id[x] = cnt++;
    for (int y : g[x]) d[y] = d[x] + 1, dfs(y);
}


int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    for (int k = K; k --> 0; ) if ((d[u] - d[v]) >> k & 1) u = fa[u][k];
    assert(d[u] == d[v]);
    if (u == v) return u;
    for (int k = K; k --> 0; ) if (fa[u][k] != fa[v][k]) u = fa[u][k], v = fa[v][k];
    assert(fa[u][0] == fa[v][0] && fa[u][0]);
    return fa[u][0];
}

mat jump(int u, int x) {
    mat mt = {{{1, 0}, {0, 1}}};
    for (int k = K; k --> 0; ) if (x >> k & 1) {
        mt = mtx[u][k] * mt;
        u = fa[u][k];
    }
    return mt;
}

int32_t main() {
    int q; cin >> n >> q;
    in.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> fa[i][0];
        g[fa[i][0]].push_back(i);
    }
    dfs(1);
    loop(k, K - 1) for (int i = 1; i <= n; i++) {
        fa[i][k + 1] = fa[fa[i][k]][k];
        mtx[i][k + 1] = mtx[fa[i][k]][k] * mtx[i][k];
    }
    mtx[1][0] = dp[1] = {{{1, 0}, {0, 1}}};
    for (int t : {1, 0}) for (int i = 2; i <= n; i++) {
        int x; cin >> x;
        mtx[i][0][t][1] = x;
        mtx[i][0][t][0] = 1 - x;
    }
    while (q--) {
        int c, p; cin >> c >> p;
        for (int x : v) in[x] = 0;
        v.resize(c);
        for (int &x : v) { cin >> x; in[x] = 1; }
        sort(v.begin(), v.end(), [&](int a, int b) { return id[a] < id[b]; });
        for (int i = 0; i + 1 < c; i++) v.push_back(lca(v[i], v[i + 1]));
        v.push_back(1);
        sort(v.begin(), v.end(), [&](int a, int b) { return id[a] < id[b]; });
        v.erase(unique(v.begin(), v.end()), v.end());
        assert(v[0] == 1);
        vec r = {1, 1};
        if (in[1]) r = {0, p}, p = 1;
        for (auto it = v.begin() + 1; it != v.end(); it++) {
            int p = lca(*prev(it), *it);
            mat tr = jump(*it, d[*it] - d[p]);
            dp[*it] = dp[p] * tr;
            if (in[*it]) {
                loop(i, 2) r[i] *= dp[*it][i][1];
                dp[*it] = {{{0, 1}, {0, 1}}};
            }
            for (int t : {0, 1}) assert((dp[*it][t][0] + dp[*it][t][1]) % M == 1);
        }
        cout << mint((1 - p) * r[0] + p * r[1]) << endl;
    }
}
