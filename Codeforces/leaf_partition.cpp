#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 2e5 + 1;
const int M = 998244353;
vector<int> g[N];
ll dp[N];
int n;
void dfs(int x) {
    dp[x] = 1;
    ll s = 0;
    for (int y : g[x]) {
        dfs(y);
        dp[x] = dp[x] * (dp[y] + 1) % M;
        s = (s + dp[y]) % M;
    }
    dp[x] = (dp[x] - s) % M;
    if (dp[x] < 0) dp[x] += M;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }
    dfs(1);
    cout << dp[1] << endl;
}