// http://www.usaco.org/index.php?page=viewproblem2&cpid=793
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
const int N = 7e4 + 1;
vector<int> adj[N];
int n, cnt, S[N], dp[N], ind[N], seg[4 * N], lazy[4 * N], ans[N];
void push(int i, int l, int r) {
    if (lazy[i]) {
        if (l != r) {
            lazy[2 * i] += lazy[i];
            lazy[2 * i + 1] += lazy[i];
        }
        seg[i] += lazy[i];
        lazy[i] = 0;
    }
}
int query(int i, int l, int r, int ql, int qr) {
    push(i, l, r);
    if (l > qr || r < ql) return 1e6;
    if (ql <= l && r <= qr) {
        // printf("%d %d %d %d %d %d\n", i, l, r, ql, qr, seg[i]);
        return seg[i];
    } else {
        int m = (l + r) / 2;
        return min(query(2 * i, l, m, ql, qr), query(2 * i + 1, m + 1, r, ql, qr));
    }
}
int QUERY(int ql, int qr) {
    return query(1, 0, n - 1, ql, qr);
}
void update(int i, int l, int r, int ql, int qr, int v) {
    push(i, l, r);
    if (ql > r || qr < l) return;
    if (l <= ql && qr <= r) {
        lazy[i] += v;
        push(i, l, r);
    } else {
        int m = (l + r) / 2;
        update(2 * i, l, m, ql, qr, v);
        update(2 * i + 1, m + 1, r, ql, qr, v);
        seg[i] = min(seg[2 * i], seg[2 * i + 1]);
    }
}
void UPDATE(int ql, int qr, int v) {
    update(1, 0, n - 1, ql, qr, v);
}
void set(int i, int l, int r, int q, int v) {
    // cout << i << " " << l << " " << r << " " << q << endl;
    push(i, l, r);
    if (l == r) seg[i] = v;
    else {
        int m = (l + r) / 2;
        if (q <= m) set(2 * i, l, m, q, v);
        else set(2 * i + 1, m + 1, r, q, v);
        seg[i] = min(seg[2 * i], seg[2 * i + 1]);
    }
    // cout << i << " " << l << " " << r << " " << seg[i] << endl;
}
void SET(int q, int v) {
    set(1, 0, n - 1, q, v);
}
void dfs1(int x, int p, int d) {
    ind[x] = cnt++;
    for (int y : adj[x]) {
        if (y == p) continue;
        dfs1(y, x, d + 1);
        S[x] += S[y];
    }
    S[x]++;
    if (adj[x].size() == 1) {
        // printf("setting %d to %d:\n", ind[x], d);
        SET(ind[x], d);
    }
    // printf("querying range %d-%d for node %d:\n", ind[x], ind[x] + s[x] - 1, x);
    int min_depth = QUERY(ind[x], ind[x] + S[x] - 1);
    // cout << x << " " << min_depth << " " << ind[x] << " " << s[x] << endl;
    if (min_depth - d <= d) dp[x] = 1;
    else for (int y : adj[x]) if (y != p) dp[x] += dp[y];
}
void dfs2(int x, int p) {
    // cout << x << " " << p << endl;
    dp[x] = 0;
    // if (x == 2) cout << "yes" << endl;
    if (adj[x].size() == 1) dp[x] = 1;
    else for (int y : adj[x]) {
        dp[x] += dp[y];
        // if (x == 2) cout << y << " " << dp[y] << endl;
    }
    ans[x] = dp[x];
    vector<int> pre;
    if (p) adj[x].erase(remove(adj[x].begin(), adj[x].end(), p), adj[x].end());
    for (int y : adj[x]) {
        // cout << y << " " << endl;
        if (pre.size()) pre.push_back(S[y] + pre.back());
        else pre.push_back(S[y]);
        // pre.push_back(S[y] + (pre.size() != 0) * pre.back());
    }
    int i = 0, s = pre.size(), f = adj[x][0];
    for (int& y : adj[x]) {
        int min_depth = 1e6;
        if (i) min_depth = min(min_depth, QUERY(ind[f], ind[f] + pre[i - 1] - 1));
        if (i < s - 1) min_depth = min(min_depth, QUERY(ind[*(&y + 1)], ind[*(&y + 1)] + pre[s - 1] - pre[i] - 1));
        min_depth = min(min_depth, QUERY(ind[x], ind[x]));
        int ox = dp[x], oy = dp[y];
        if (min_depth <= 1) dp[x] = 1;
        else dp[x] -= dp[y];
        if (i) UPDATE(ind[f], ind[f] + pre[i - 1] - 1, 1);
        if (i < s - 1) UPDATE(ind[*(&y + 1)], ind[*(&y + 1)] + pre[s - 1] - pre[i] - 1, 1);
        UPDATE(ind[x], ind[x], 1);
        UPDATE(ind[y], ind[y] + S[y] - 1, -1);
        dfs2(y, x);
        dp[x] = ox, dp[y] = oy;
        if (i) UPDATE(ind[f], ind[f] + pre[i - 1] - 1, -1);
        if (i < s - 1) UPDATE(ind[*(&y + 1)], ind[*(&y + 1)] + pre[s - 1] - pre[i] - 1, -1);
        UPDATE(ind[x], ind[x], -1);
        UPDATE(ind[y], ind[y] + S[y] - 1, 1);
        i++;
    }
}
int main() {
    // freopen("atlarge.in", "r", stdin);
    // freopen("atlarge.out", "w", stdout);
    fill(seg, seg + 4 * N, 1e6);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(1, 0, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
    // cout << dp[1] << endl;
}