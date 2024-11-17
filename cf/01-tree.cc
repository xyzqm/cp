// https://codeforces.com/problemset/problem/1156/D
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int N = 2e5 + 1;
vector<pii> adj[N];
ll dp[N][2], ans;
void dfs1(int x, int p) {
    for (auto [y, w] : adj[x]) {
        if (y == p) continue;
        dfs1(y, x);
        if (w == 0) {
            dp[x][0] += dp[y][0] + 1;
        } else {
            dp[x][1] += dp[y][0] + dp[y][1] + 1;
        }
    }
}
void dfs2(int x, int p) {
    ans += dp[x][0] + dp[x][1];
    ll x0 = dp[x][0], x1 = dp[x][1];
    for (auto [y, w] : adj[x]) {
        if (y == p) continue;
        ll y0 = dp[y][0], y1 = dp[y][1];
        if (w == 0) {
            dp[x][0] -= dp[y][0] + 1;
            dp[y][0] += dp[x][0] + 1;
        } else {
            dp[x][1] -= dp[y][0] + dp[y][1] + 1;
            dp[y][1] += dp[x][0] + dp[x][1] + 1;
        }
        dfs2(y, x);
        dp[x][0] = x0, dp[x][1] = x1;
        dp[y][0] = y0, dp[y][1] = y1;
    }
}

int main() {
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y, w; cin >> x >> y >> w;
        adj[x].push_back({y, w});
        adj[y].push_back({x, w});
    }
    dfs1(1, 0);
    dfs2(1, 0);
    cout << ans << endl;
}