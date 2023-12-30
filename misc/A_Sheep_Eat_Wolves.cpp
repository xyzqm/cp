#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
using T = tuple<int, int, int>;
const int N = 101;
int x, y, p, q;
int dp[N][N][2];
int smin(int& a, int b) { return a = min(a, b); }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> x >> y >> p >> q;
  for (int i = 0; i <= x; i++) for (int j = 0; j <= y; j++) dp[i][j][0] = dp[i][j][1] = -1;
  queue<T> Q;
  // we start on side k = 1
  for (int i = 0; i <= y; i++) {
    dp[x][i][0] = 0;
    Q.push({x, i, 0});
  }
  while (Q.size() && Q.front() != T{x, y, 1}) {
    auto [i, j, k] = Q.front();
    Q.pop();
    for (int h = 0; h <= min(i, p); h++) {
      for (int l = 0; l <= min(j, p - h); l++) {
        int I = x - i + h, J = y - j + l, K = 1 - k;
        if (i - h && j - l > i - h + q || dp[I][J][K] >= 0) continue;
        dp[I][J][K] = dp[i][j][k] + 1;
        Q.push({I, J, K});
      }
    }
  }
  cout << (dp[x][y][1] == inf ? -1 : dp[x][y][1]) << endl;
  return 0;
}