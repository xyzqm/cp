#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>
using namespace std;
#define int long long
using i2 = pair<int, int>;
using i3 = tuple<int, int, int>;
const int N = 1e5 + 1;
const int M = 1e9 + 7;
int dp[N][5][5][5];
int ki(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    if (c == 'T') return 3;
    return -1;
}
int ad(int& a, int b) { return a = (a + b) % M; }
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int i = 0; i < 4; i++) dp[0][i][4][4] = 1;
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 5; k++) {
                for (int h = 0; h < 5; h++) {
                    if (!dp[i][j][k][h]) continue;
                    for (int c = 0; c < 4; c++) if (c == ki(s[i]) || s[i] == '?') {
                        if (c != h) { // can choose to extend current group
                            ad(dp[i + 1][j][(k == 4) ? c : k][c], dp[i][j][k][h]);
                            if (c == j) { // choose to end group with character c
                                ad(dp[i + 1][(k == 4) ? c : k][4][4], dp[i][j][k][h]);
                            }
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 4; i++) ad(ans, dp[s.length()][i][4][4]);
    cout << ans << endl;
}
