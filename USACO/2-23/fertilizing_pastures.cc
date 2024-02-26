// http://www.usaco.org/index.php?page=viewproblem2&cpid=1306
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 1;
int n, t, a[N], p[N], sum[N], sz[N], dp[N], dp2[N], d[N];
vector<int> adj[N];
void vis(int i) {
    sz[i] = 1, sum[i] = a[i], d[i] = 0;
    for (int x : adj[i]) {
        vis(x);
        sz[i] += sz[x];
        sum[i] += sum[x];
        d[i] = max(d[i], d[x] + 1);
    }
    sort(adj[i].begin(), adj[i].end(), [](int a, int b) {
        return sz[a] * sum[b] < sz[b] * sum[a];
    });
    int pre = 0;
    for (int x : adj[i]) {
        dp[i] += dp[x] + (2 * pre + 1) * sum[x];
        pre += sz[x];
    }
    if (t == 0) return;
    if (adj[i].size() == 0) return;
    dp2[i] = LLONG_MAX;
    int suf = 0, suf2 = 0;
    for (int j = adj[i].size() - 1; j >= 0; j--) {
        int x = adj[i][j];
        suf2 += sz[x];
        if (d[x] != d[i] - 1) {
            suf += sum[x];
            continue;
        }
        dp2[i] = min(
            dp2[i], 
            dp[i] + (dp2[x] - dp[x]) - 2 * sz[x] * suf + (2 * (suf2 - sz[x])) * sum[x]
        );
        suf += sum[x];
    }
}
signed main() {
    cin >> n >> t;
    for (int i = 2; i <= n; i++) {
        cin >> p[i] >> a[i];
        adj[p[i]].push_back(i);
    }
    vis(1);
    if (t == 0) cout << 2 * (n - 1) << " " << dp[1] << endl;
    else cout << 2 * (n - 1) - d[1] << " " << dp2[1] << endl;
}