// https://cses.fi/problemset/task/1139
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int N = 2e5 + 1;
vector<int> adj[N], order;
struct range {
    int l, r, i;
};
int n, color[N], sz[N], mp[N], sum[4 * N], ans[N];
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
void dfs(int x, int p) {
    order.push_back(x);
    mp[x] = order.size();
    sz[x]++;
    for (int y : adj[x]) {
        if (y == p) continue;
        dfs(y, x);
        sz[x] += sz[y];
    }
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> color[i];
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b); adj[b].push_back(a);
    }
    dfs(1, 0);
    vector<range> ranges;
    for (int i = 1; i <= n; i++) {
        ranges.push_back({mp[i], mp[i] + sz[i] - 1, i});
    }
    sort(ranges.begin(), ranges.end(), [] (range a, range b) {
        return a.r < b.r;
    });
    auto it = ranges.begin();
    for (int r = 1; r <= n; r++) {
        int x = order[r - 1];
        if (prv[color[x]]) update(prv[color[x]], 0);
        update(prv[color[x]] = r, 1);
        while (it != ranges.end() && (*it).r == r) {
            ans[(*it).i] = query((*it).l, (*it).r);
            it = next(it);
        }
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;
}