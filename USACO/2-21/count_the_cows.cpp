#include <bits/stdc++.h>
#define int long long
using namespace std;
using vi = vector<int>;
const int D = 39; // max number of digits (+buffer)
int dp[D + 1][2][2][3];
int DP(vi& x, vi& y, vi& d) {
    x.resize(D);
    y.resize(D);
    d.resize(D);
    memset(dp, 0, sizeof dp);
    dp[0][0][0][1] = 1;
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                int nxt;
                if (j == 0) nxt = ((k > d[i]) ? 2 : 0);
                else if (j == 1) {
                    if (k < d[i]) nxt = 0;
                    else if (k == d[i]) nxt = 1;
                    else nxt = 2;
                }
                else nxt = ((k < d[i]) ? 0 : 2);
                int x1 = (x[i] + k) / 3;
                int x2 = (x[i] + k) % 3;
                int y1 = (y[i] + k) / 3;
                int y2 = (y[i] + k) % 3;
                for (int a = 0; a < 2; a++) {
                    for (int b = 0; b < 2; b++) {
                        int x1 = (x[i] + a + k) / 3;
                        int x2 = (x[i] + a + k) % 3;
                        int y1 = (y[i] + b + k) / 3;
                        int y2 = (y[i] + b + k) % 3;
                        if (x2 % 2 == y2 % 2) {
                            dp[i + 1][x1][y1][nxt] += dp[i][a][b][j];
                        }
                    }
                }
            }
        }
    }
    return dp[D][0][0][0] + dp[D][0][0][1];
}
signed main() {
    int q; cin >> q;
    while (q--) {
        vi vd, vx, vy;
        int d, x, y;
        cin >> d >> x >> y;
        while (d) vd.push_back(d % 3), d /= 3;
        while (x) vx.push_back(x % 3), x /= 3;
        while (y) vy.push_back(y % 3), y /= 3;
        cout << DP(vx, vy, vd) << endl;
    }
}