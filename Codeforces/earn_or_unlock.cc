// https://codeforces.com/problemset/problem/1854/B
#include <iostream>
#include <bitset>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e5 + 1;

int n, a[N], p[N];
bitset<2 * N> dp;

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    p[i] = p[i - 1] + a[i];
  }
  dp = 2;
  for (int i = 1; i <= n; i++) dp |= (dp >> i << (i + a[i]));
  int r = 0;
  for (int i = 1; i <= 2 * n; i++) if (dp[i]) r = max(r, p[min(i, n)] - i + 1);
  cout << r << endl;
}
