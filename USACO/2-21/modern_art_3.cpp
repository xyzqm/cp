// unfinished
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cassert>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
using T = tuple<int, int, int>;
const int N = 300;
int n, c[N], dp[N][N][N];
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    // cout << n << endl;
    for (int i = 0; i < n; i++) cin >> c[i], --c[i];
    for (int i = 0; i < n; i++) dp[i][i][c[i]] = 0;
    for (int i = n; --i >= 0; ) {
        for (int j = i; j < n; j++) {
            for (int k = 0; k < n; k++) {

            }
            // assert(J == 0 || c[J] != c[j]);
            // cout << i << " " << I << " " << j << " " << J << endl;
            dp[i][j] = inf;
            if (c[i] == c[j]) dp[i][j] = 1 + ((I > J) ? 0 : dp[I][J]);
            if (I <= J) dp[i][j] = min(dp[i][j], 1 + min(dp[I][j], dp[i][J]));
        }
    }
    cout << dp[0][n - 1];
    return 0;
}