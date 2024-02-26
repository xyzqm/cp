#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e3 + 1;
// If each node has max value 1000 and we spend T time,
// our final profit is 1000T - CT^2
// in order for this to be positive, T <= 1000
const int T = 1e3 + 1;
// dp[t][i] -> max reward if we're at node i at time t
int m[N], dp[T][N];
vector<int> adj[N];
int n, M, C;
signed main() {
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    cin >> n >> M >> C;
    for (int i = 1; i <= n; i++) cin >> m[i];
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }
    int ans = 0;
    for (int i = 0; i < T; i++) for (int j = 1; j <= n; j++) dp[i][j] = INT_MIN;
    dp[0][1] = 0;
    for (int t = 0; t < T; t++) {
        ans = max(ans, dp[t][1]);
        if (t == t - 1) break;
        for (int i = 1; i <= n; i++) {
            for (int j : adj[i]) {
                dp[t + 1][j] = max(dp[t + 1][j], dp[t][i] + m[j] - C * (2*t + 1));
            }
        }
    }
    cout << ans;
} 