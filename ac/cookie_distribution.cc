// https://atcoder.jp/contests/dwacon6th-prelims/tasks/dwacon6th_prelims_c
#include <iostream>
#define int long long
using namespace std;

const int inf = 1e18;

const int N = 1e3 + 1;
const int K = 21;
int n, k, a[K], dp[K][N];

const int M = 1e9 + 7;
int E(int x, int y) {
  int r = 1;
  for (y <<= 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x % M;
  return r;
}
int inv(int x) { return E(x, M - 2); }
int ad(int& x, int y) { return x = (x + y) % M; }

int F[N], F_i[N];
void pre(int n) { F[0] = F_i[0] = 1; for (int i = 1; i < n; i++) F_i[i] = inv(F[i] = F[i - 1] * i % M); }
int C(int n, int k) { return F[n] * F_i[n - k] % M * F_i[k] % M; }

signed main() {
  pre(N);
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n >> k;
  for (int i = 0; i < k; i++) cin >> a[i];
  dp[0][0] = 1;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j <= n; j++) if (dp[i][j]) {
      for (int h = 0; h <= min(n - j, a[i]); h++) {
        ad(dp[i + 1][j + h], C(n - j, h) * C(n - h, a[i] - h) % M * dp[i][j] % M); 
      }
    }
  }
  cout << dp[k][n] << endl;

}
