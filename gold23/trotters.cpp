#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1e5 + 1;
ll dp[N][6], a[N], t[N];
vector<int> g[N];
int n;
void dfs(int x, int p) {
    ll tot = 0, m1 = 0, m2 = 0, m3 = 0;
    for (int y : g[x]) if (y != p) {
        dfs(y, x);
        tot += dp[y][4];
        if (dp[y][3] - dp[y][4] > dp[m1][3] - dp[m1][4]) m2 = m1, m1 = y;
        else if (dp[y][3] - dp[y][4] > dp[m2][3] - dp[m2][4]) m2 = y;
        if (dp[y][1] - dp[y][4] > dp[m3][1] - dp[m3][4]) m3 = y;
    }
    dp[x][0] = tot + dp[m3][1] - dp[m3][4];
    dp[x][5] = tot;
    for (int y : g[x]) if (y != p) {
        // if (x == 1) printf("%d %lld %lld %lld %lld %lld\n", y, a[y], m1, m2, dp[y][5], tot);
        ll cur = tot + a[y] - dp[y][4] + dp[y][5];
        if (m1 != y) cur += dp[m1][3] - dp[m1][4];
        else cur += dp[m2][3] - dp[m2][4];
        // cout << cur << endl;
        dp[x][0] = max(dp[x][0], cur);
    }
    for (int i = 1; i < 5; i++) dp[x][i] = dp[x][0];
    for (int i = 0; i <= t[x]; i++) dp[x][i] += a[x];
    // printf("%d:\n", x);
    // for (int i = 0; i < 6; i++) cout << dp[x][i] << " ";
    // cout << endl;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> t[i];
        for (int i = 1; i <= n; i++) {
            g[i].clear();
            for (int j = 0; j < 6; j++) dp[i][j] = 0;
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1, 0);
        cout << dp[1][0] << endl;
    }
}