#include <bits/stdc++.h>
using namespace std;
#define loop(i, l, r) for (int i = l; i < r; i++)

const int N = 5e5 + 1;
int n, dep[N], tin[N], dfs_t = 0;

const int K = 20;
int st[2 * N][K];

// O(1) LCA
int lg(int x) { return 31 - __builtin_clz(x); }
int min_d(int x, int y) { return dep[x] < dep[y] ? x : y; }
void build() {
    loop(k, 0, K - 1) {
        loop(i, 0, dfs_t) {
            st[i][k + 1] = min_d(st[i][k], st[min(i + (1 << k), dfs_t - 1)][k]);
        }
    }
}
int lca(int u, int v) {
    u = tin[u], v = tin[v];
    if (u > v) swap(u, v);
    int k = lg(++v - u);
    return min_d(st[u][k], st[v - (1 << k)][k]);
}
int dist(int u, int v) { return dep[u] + dep[v] - 2 * lca(u, v); }

// DFS
vector<int> g[N];
void dfs(int x, int p) {
    dep[x] = dep[p] + 1;
    for (int y : g[x]) {
        st[tin[x] = dfs_t++][0] = x;
        if (y == p) continue;
        dfs(y, x);
    }
}

#define int int64_t
int m, s, t[N], x[N], d[N];

bool ck(int v) {
    // we can be at any point within radius ex of point u
    int ex = 0, u = s, lt = 0;
    loop(i, 0, m) {
        ex += v * (t[i] - lt) - dist(u, x[i]);
        if (ex < -d[i]) return 0;
        else ex = min(d[i], ex);
        // check if path from i - 1 -> i intersects with i -> i + 1
        if (i < m - 1) {
            int w = lca(x[i], x[i + 1]);
            if (d[u] < d[x[i]]) {

            }
        }
        lt = t[i], u = x[i];
    }
    return 1;
}

void ac() {
    dfs_t = 0; // reset euler tour timer
    // take input
    cin >> n >> m >> s;
}

int32_t main() {

}
