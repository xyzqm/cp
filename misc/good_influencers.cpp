#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
using ll = long long;
const int N = 2e5 + 1;
const ll inf = INT_MAX;
int n; 
ll dp[N][2][2], C[N];
vector<int> g[N];
bool on[N];
void dfs(int x, int p) {
    ll mn10 = inf, mn11 = inf;
    for (int y : g[x]) if (y != p) {
        dfs(y, x);
        ll mn0 = min(dp[y][0][0], dp[y][0][1]);
        ll mn1 = min(dp[y][1][0], dp[y][1][1]);
        // guaranteed < inf
        ll mn4 = min(mn0, mn1);
        if (!on[x]) {
            dp[x][0][0] += mn1;
            dp[x][0][1] += mn4;
        }
        dp[x][1][0] += mn1;
        mn10 = min(mn10, dp[y][1][1] - mn1);
        dp[x][1][1] += mn4;
        mn11 = min(mn11, dp[y][1][1] - mn4);
    }
    if (!on[x]) {
        dp[x][1][0] += mn10;
        dp[x][1][1] += mn11;
        dp[x][0][1] += C[x];
    } 
    dp[x][1][1] += C[x];
    // printf("%d %lld %lld %lld %lld\n", x, dp[x][0][0], dp[x][0][1], dp[x][1][0], dp[x][1][1]);
}
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        on[i] = (c == 'Y');
        if (on[i]) dp[i][0][0] = dp[i][0][1] = inf;
    }
    for (int i = 1; i <= n; i++) cin >> C[i];
    dfs(1, 0);
    cout << min(dp[1][1][0], dp[1][1][1]) << endl;
}