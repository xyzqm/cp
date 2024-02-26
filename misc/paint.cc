#include <iostream>
#include <set>
using namespace std;
#define int long long
const int N = 5e4 + 1;
int n, c[N], dp[N], ind[N];
set<int, greater<int>> s;
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> c[i];
    fill(dp, dp + N, 1e10);
    dp[0] = 0;
    s.insert(0);
    for (int i = 1; i <= n; i++) {
        if (ind[c[i]]) s.erase(ind[c[i]]);
        s.insert(ind[c[i]] = i);
        int cnt = 0;
        for (int j : s) {
            // cout << j << " ";
            dp[i] = min(dp[i], dp[j] + cnt * cnt);
            cnt++;
            if (cnt * cnt > n) break;
        }
        // cout << endl;
        // cout << dp[i] << " ";
    }
    // cout << endl;
    cout << dp[n] << endl;
    return 0;
}