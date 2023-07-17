#include <iostream>
#include <vector>
#define COMB(a, b) (a) + (b)
using namespace std;
using ll = long long;
const int N = 2e5 + 1;
int T = 0, n, q, I[N], E[N];
vector<int> g[N];
// segtree template
ll v[N], seg[4 * N], lazy[4 * N];
void push(int p, int l, int r) {
    if (lazy[p]) {
        seg[p] += lazy[p] * (r - l + 1);
        if (l != r) {
            lazy[2 * p] += lazy[p];
            lazy[2 * p + 1] += lazy[p];
        }
        lazy[p] = 0;
    }
}
ll query(int i, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if (l == r) return seg[p];
    int m = (l + r) / 2;
    if (i <= m) return query(i, 2 * p, l, m);
    else return query(i, 2 * p + 1, m + 1, r);
}
void update(int i, int j, ll x, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if (r < i || l > j) return;
    else if (i <= l && r <= j) {
        lazy[p] += x;
        push(p, l, r);
    } else {
        int m = (l + r) / 2;
        update(i, j, x, 2 * p, l, m);
        update(i, j, x, 2 * p + 1, m + 1, r);
        seg[p] = COMB(seg[2 * p], seg[2 * p + 1]);
    }
}
// end segtree template
void dfs(int x, int p) {
    I[x] = ++T;
    for (int y : g[x]) if (y != p) dfs(y, x);
    E[x] = T;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> v[i];
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y); 
        g[y].push_back(x);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) update(I[i], E[i], v[i]);
    while (q--) {
        int t, s;
        cin >> t >> s;
        if (t == 1) {
            ll x;
            cin >> x;
            update(I[s], E[s], x - v[s]);
            v[s] = x;
        } else cout << query(I[s]) << endl;
    }
}