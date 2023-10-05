#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cstring>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
using T = tuple<int, int, int>;
const int N = 18;
int n, q;
int p[N][N];
int dp[1 << N][N], ans[1 << N];
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            p[i][--x] = j;
        }
    }
    for (int i = 0; i < n; i++) dp[1 << i][i] = 1;
    for (int i = 0; i < 1 << n; i++) {
        for (int j = 0; j < n; j++) if (dp[i][j]) {
            for (int k = 0; k < n; k++) if (p[k][j] <= p[k][k]) {
                int I = __builtin_clzll(i), K = __builtin_clzll(1 << k);
                if (I == K) {
                    ans[i] += dp[i][j];
                    for (int h = 64 - I; h < n; h++) dp[i | 1 << h][h] += dp[i][j];
                } else if (K > I && !(i >> k & 1)) dp[i | 1 << k][k] += dp[i][j]; 
            }
        }
    }
    ans[0] = 1;
    cin >> q;
    while (q--) {
        int h = 0, g = 0;
        for (int i = 0; i < n; i++) {
            char c; cin >> c;
            if (c == 'H') h |= 1 << i;
            else g |= 1 << i;
        }
        cout << ans[h] * ans[g] << '\n';
    }
    return 0;
}