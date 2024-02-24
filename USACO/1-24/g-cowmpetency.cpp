#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
const int Q = 101;
const int C = 1e4 + 2;
const int M = 1e9 + 7;
int n, q, c, dp[Q][C], DP[Q][C];
P a[Q];
int E(int x, int y) {
  assert(y >= 0);
  int r = 1;
  for (y <<= 1; y >>= 1; x = x * x % M)
    if (y & 1)
      r = r * x % M;
  return r;
}
int S(int x, int y) { return ((x - y) % M + M) % M; }
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> q >> c;
  map<int, int> m;
  for (int i = 1; i <= q; i++) {
    int x, y;
    cin >> x >> y;
    m[y] = m[y] ? min(m[y], x) : x;
  }
  q = 0;
  for (auto [y, x] : m)
    a[++q] = {x, y};
  sort(a, a + q);
  dp[0][0] = 1;
  for (int i = 1; i <= c; i++)
    DP[0][i] = 1;
  for (int i = 1; i <= q; i++) {
    for (int j = i; j <= c; j++) {
      dp[i][j] =
          dp[i][j - 1] +
          dp[i - 1][j - 1] * E(j - 1, a[i].second - a[i - 1].second - 1) % M +
          DP[i - 1][j - 1] *
              S(E(j - 1, a[i].first - a[i - 1].second),
                E(j - 2, a[i].first - a[i - 1].second)) %
              M * E(j - 1, a[i].second - a[i].first - 1) % M;
      dp[i][j] %= M;
      DP[i][j + 1] = (DP[i][j] + dp[i][j]) % M;
    }
  }
  cout << DP[q][c + 1] * E(c, n - a[q].second) % M << endl;
  return 0;
}
