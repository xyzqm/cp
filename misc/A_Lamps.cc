// https://oj.uz/problem/view/JOI19_lamps
#include <iostream>
using namespace std;
#define int long long
const int inf = 1e18;
const int N = 1e6 + 1;
int n, dp[N][8];
string s, t;
int smin(int& a, int b) { return a = min(a, b); }
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  cin >> s >> t;
  for (int i = 0; i <= n; i++) for (int j = 0; j < 8; j++) dp[i][j] = inf;
  for (int i = 0; i < 8; i++) dp[0][i] = __builtin_popcount(i);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 8; j++) {
      if (((j & 0b110 ? (j & 0b010) > 0 : s[i] - '0') ^ (j & 0b001)) == t[i] - '0') { // can transition!
        for (int k = 0; k < 8; k++) smin(dp[i + 1][k], dp[i][j] + __builtin_popcount(j ^ k));
      }
    }
  }
  cout << dp[n][0] / 2 << endl;
  return 0;
}