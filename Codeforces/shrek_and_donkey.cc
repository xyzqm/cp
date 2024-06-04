// https://codeforces.com/contest/98/problem/E
#include <iomanip>
#include <ios>
#include <iostream>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e3 + 1;

int n, m;
long double dp[N][N];

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n >> m;
  int k = max(n, m);
  for (int i = 0; i <= k; i++) dp[i][0] = 1;
  for (int i = 0; i <= k; i++) dp[0][i] = 1.0 / (i + 1);
  for (int s = 2; s <= 2 * k; s++) {
    for (int i = 1, j = s - 1; i <= k && j > 0; i++, j--) if (j <= k) {
      long double a = j * (1 - dp[j - 1][i]); 
      long double b = (j + 1) * dp[j][i - 1];
      long double p = (j + 1 - a) / (1 + b);
      dp[i][j] = 1 - p * dp[j][i - 1];
    }
  }
  cout << fixed << setprecision(9) << dp[n][m] << " " << 1 - dp[n][m] << endl;
}
