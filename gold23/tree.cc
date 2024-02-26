#include <iostream>
#include <vector>
#define UPD(a, b) a = max(a, b)
using namespace std;
using ll = long long;
const int N = 152;
const ll inf = 1e18;
vector<int> adj[N];
int n, dist[N], ans[N], P[N], S[N], mx = 0;
ll A[N], dp[N][N][N];
void dfs(int x, int p) {
    P[x] = p;
    ans[x] = max(ans[x], dist[x] = dist[p] + 1);
    if (dist[x] > dist[mx]) mx = x;
    S[x] = 1;
    for (int y : adj[x]) if (y != p) {
        dfs(y, x);
        S[x] += S[y];
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        ll S = 0;
        for (int i = 0; i < n; i++) {
            cin >> A[i];
            S += A[i];
        }
        for (int i = 0; i < n; i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        cout << S << endl;
        // dist[0] = -1;
        // dfs(1, 0);
        // dfs(mx, 0);
        // dfs(mx, 0);
        // vector<int> D;
        // while (mx) D.push_back(mx), mx = P[mx];
        // reverse(D.begin(), D.end());
        // for (int x : D) cout << x << " ";
        // cout << endl;
        // for (int i = 0; i < D.size() ; i++) {
        //     for (int j = 0; j <= n; j++) {
        //         for (int k = 0; k <= n; k++) dp[i][j][k] = -inf;
        //     }
        // }
        // dp[0][0][0] = 0; // node, index, wastable space
        // for (int i = 0; i < D.size(); i++) {
        //     for (int j = 0; j < n; j++) {
        //         for (int k = 0; k < n; k++) {
        //             if (dp[i][j][k] == -inf) continue;
        //             printf("%d %d %d %lld\n", i, j, k, dp[i][j][k]);
        //             if (i + 1 < D.size()) {
        //                 int w = 0;
        //                 if (i + 2 < D.size()) w = S[D[i + 1]] - S[D[i + 2]] - 1;
        //                 UPD(dp[i + 1][j + 1][k + w], dp[i][j][k] + A[j]);
        //             }
        //             if (k) UPD(dp[i][j + 1][k - 1], dp[i][j][k]);
        //         }
        //     }
        // }
        // cout << dp[D.size()][n][0];
        // cout << endl;
    }
}