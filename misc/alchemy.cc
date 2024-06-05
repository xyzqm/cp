// https://open.kattis.com/contests/ubpxnk/problems/alchemy2
#include <iostream>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 101;

int dp[N][N][2];

int smin(int& a, int b) { return a = min(a, b); }

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  string s; cin >> s;
  int n = s.length();
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) for (int k = 0; k < 2; k++) dp[i][j][k] = inf;
  for (int i = n; i --> 0; ) {
    for (int j = i; j < n; j++) {
      for (int k = 0; k < 2; k++) { // k = 1: s[i] != s[j]
        if (i == j) dp[i][j][k] = 0;
        else if (j == i + 1) dp[i][j][k] = k;
        else {
          // fix one side
          if (k) {
            if (s[i + 1] != s[j - 1]) smin(dp[i][j][k], 1 + dp[i + 1][j - 1][0]);
            smin(dp[i][j][k], 1 + dp[i + 1][j - 1][1]);
          }
          // fix both sides
          smin(dp[i][j][k], 2 + (i + 2 <= j - 2 ? dp[i + 2][j - 2][s[i + 2] != s[j - 2]] : 0));
          if (!k) smin(dp[i][j][k], dp[i + 1][j - 1][s[i + 1] != s[j - 1]]);
        }
      }
    }
  }
  cout << dp[0][n - 1][s[0] != s[n - 1]] << endl;
}
