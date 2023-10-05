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
int w[1 << N], dp[1 << N], t[1 << N][N];
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            --x;
            p[i][x] = j;
        }
    }
    for (int i = 0; i < n; i++) {
        t[1 << i][i] = 1;
        for (int _ = 0; _ < (1 << (n - i)); _++) {
            int j = _ << i;
            for (int k = i; k < n; k++) {
                if (!t[j][k]) continue;
                for (int h = i; h < n; h++) if (p[h][k] <= p[h][h]) {
                    if (h == i) w[j] += t[j][k];
                    else if (!(j >> h & 1)) t[j | (1 << h)][h] += t[j][k];
                }
            }
        }
    }
    dp[0] = 1;
    for (int i = 1; i < 1 << n; i++) {
        for (int j = i; j; j = (j - 1) & i) if ((i & -i) == (j & -j)) dp[i] += w[j] * dp[i - j];
    }
    cin >> q;
    while (q--) {
        int h = 0, g = 0;
        for (int i = 0; i < n; i++) {
            char c; cin >> c;
            if (c == 'H') h |= 1 << i;
            else g |= 1 << i;
        }
        cout << dp[h] * dp[g] << '\n';
    }
    return 0;
}