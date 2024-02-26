// http://www.usaco.org/index.php?page=viewproblem2&cpid=696
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int N = 2e5 + 1;
vector<int> adj[N], order;
int n, p[N], sz[N], mp[N], sum[4 * N], ans[N];
map<int, int> prv;
int _query(int p, int l, int r, int i, int j) {
    if (r < i || l > j) return 0;
    if (i <= l && r <= j) return sum[p];
    int m = (l + r) / 2;
    return _query(2 * p, l, m, i, j) + _query(2 * p + 1, m + 1, r, i, j);
}
int query(int l, int r) {
    return _query(1, 1, n, l, r);
}
void _update(int p, int l, int r, int i, int x) {
    if (l == r) sum[p] = x;
    else {
        int m = (l + r) / 2;
        if (i <= m) _update(2 * p, l, m, i, x);
        else _update(2 * p + 1, m + 1, r, i, x);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
}
void update(int i, int x) {
    return _update(1, 1, n, i, x);
}
void dfs(int x) {
    order.push_back(x);
    mp[x] = order.size();
    sz[x]++;
    for (int y : adj[x]) {
        dfs(y);
        sz[x] += sz[y];
    }
}
int main() {
    // freopen("promote.in", "r", stdin);
    // freopen("promote.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    set<pii, greater<pii>> s;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        s.insert({p[i], i});
    }
    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        adj[p].push_back(i);
    }
    dfs(1);
    for (pii cur : s) {
        int i = cur.second;
        ans[i] = query(mp[i], mp[i] + sz[i] - 1);
        update(mp[i], 1);
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
}