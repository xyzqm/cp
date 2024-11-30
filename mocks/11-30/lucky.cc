#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2e4 + 1;
const int K = 16;
vector<int> B[N][K], g[N];
int f[N][K], v[N], d[N];
int n, q;

vector<int> merge(const vector<int> &a, const vector<int> &b) { // basis vectors in decreasing order
    array<vector<int>, 66> v;
    for (int x : a) if (x) v[__builtin_clzll(x)].push_back(x);
    for (int x : b) if (x) v[__builtin_clzll(x)].push_back(x);
    vector<int> c;
    for (int i = 0; i < 66; i++) if (v[i].size()) {
        c.push_back(v[i].back());
        v[i].pop_back();
        while (v[i].size()) {
            int x = v[i].back() ^ c.back();
            if (x) v[__builtin_clzll(x)].push_back(x);
            v[i].pop_back();
        }
    }
    return c;
}

void dfs(int x) {
    d[x] = d[f[x][0]] + 1;
    B[x][0] = vector<int>(1, v[x]);
    for (int k = 1; k < K; k++) {
        f[x][k] = f[f[x][k - 1]][k - 1];
        B[x][k] = merge(B[x][k - 1], B[f[x][k - 1]][k - 1]);
    }
    for (int y : g[x]) if (y != f[x][0]) {
       dfs((f[y][0] = x, y));
    }
}

signed main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> v[i];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);
    while (q--) {
        int u, v; cin >> u >> v;
        if (d[u] < d[v]) swap(u, v);
        vector<int> b;
        for (int k = 0; k < K; k++) if ((d[u] - d[v]) >> k & 1) {
            b = merge(b, B[u][k]);
            u = f[u][k];
        }
        for (int k = K; k --> 0; ) if (f[u][k] != f[v][k]) {
            b = merge(b, B[u][k]);
            b = merge(b, B[v][k]);
            u = f[u][k];
            v = f[v][k];
        }
        b = merge(b, {::v[u]});
        b = merge(b, {::v[v]});
        if (u != v) b = merge(b, {::v[f[u][0]]});
        int r = 0;
        for (int x : b) r = max(r, r ^ x);
        cout << r << endl;
    }
}
