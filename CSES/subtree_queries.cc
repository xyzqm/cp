#include <iostream>
#include <vector>
#define COMB(a, b) a + b
using namespace std;
using ll = long long;
const int N = 2e5 + 1;
ll seg[4 * N], v[N], a[N];
int n, q, I[N], E[N], T;
vector<int> g[N];
// start segtree
ll query(int i, int j, int p = 1, int l = 1, int r = n) {
    if (r < i || l > j) return 0;
    if (i <= l && r <= j) return seg[p];
    int m = (l + r) / 2;
    return COMB(query(i, j, 2 * p, l, m), query(i, j, 2 * p + 1, m + 1, r));
}
void upd(int i, int x, int p = 1, int l = 1, int r = n) {
    if (l == r) seg[p] = x;
    else {
        int m = (l + r) / 2;
        if (i <= m) upd(i, x, 2 * p, l, m);
        else upd(i, x, 2 * p + 1, m + 1, r);
        seg[p] = COMB(seg[2 * p], seg[2 * p + 1]);
    }
}
void build(int p = 1, int l = 1, int r = n) {
    if (l == r) seg[p] = a[l];
    else {
        int m = (l + r) / 2;
        build(2 * p, l, m); 
        build(2 * p + 1, m + 1, r);
        seg[p] = COMB(seg[2 * p], seg[2 * p + 1]);
    }
}
// end segtree
void dfs(int u = 1, int p = 0) {
    a[I[u] = ++T] = v[u];
    for (int v : g[u]) if (v != p) dfs(v, u);
    E[u] = T;
}
int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> v[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs();
    build();
    while (q--) {
        int t, s;
        cin >> t >> s;
        if (t == 1) {
            ll x;
            cin >> x;
            upd(I[s], x);
        } else cout << query(I[s], E[s]) << endl;
    }
}