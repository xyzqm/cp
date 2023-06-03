// https://atcoder.jp/contests/dp/tasks/dp_v?lang=en
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 1;
vector<int> adj[N];
int n, M;
ll ans[N], f[N];
ll dfs1(int x, int p) {
    f[x] = 1;
    for (int y : adj[x]) {
        if (y != p) f[x] = (f[x] * (dfs1(y, x) + 1)) % M;
    }
    return f[x];
}
void dfs2(int x, int p) {
    ans[x] = f[x];
    int i = 0;
    vector<ll> pre(adj[x].size()), suf(adj[x].size());
    for (int y : adj[x]) {
        if (y == p) continue;
        pre[i] = (f[y] + 1) % M;
        if (i) pre[i] = (pre[i] * pre[i - 1]) % M;
        i++;
    }
    int s = i;
    int j = adj[x].size();
    while (i) {
        if (adj[x][--j] == p) continue;
        i--;
        suf[i] = (f[adj[x][j]] + 1) % M;
        if (i < s - 1) suf[i] = (suf[i] * suf[i + 1]) % M;
    }
    for (int y : adj[x]) {
        if (y == p) continue;
        int ox = f[x], oy = f[y];
        f[x] = (f[p] + 1) % M;
        if (i > 0) f[x] = (f[x] * pre[i - 1]) % M;
        if (i < s - 1) f[x] = (f[x] * suf[i + 1]) % M;
        f[y] = (f[y] * (f[x] + 1)) % M;
        dfs2(y, x);
        f[x] = ox, f[y] = oy;
        i++;
    }
}
int main() {
    cin >> n >> M;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << endl;
}