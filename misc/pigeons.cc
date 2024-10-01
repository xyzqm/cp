const int A = 500001;
const int M = 998244353;
const int N = 51;
const int K = 1e3 + 1;
#include "mint.h"
#include "combo.h"

mint ev[N * K][N], p[N * K][N], inv[N];

int main() {
  pre();
  int n, k; cin >> n >> k;
  p[0][0] = 1;
  for (int i = 1; i <= n; i++) inv[i] = mint{1} / i;
  for (int i = 0; i < n * k; i++) {
    for (int j = 0; j < n; j++) {
      p[i + 1][j] += p[i][j] * inv[n - j];
      ev[i + 1][j] += (ev[i][j] + p[i][j] * n * inv[n - j]) * inv[n - j];
      p[i + 1][j + 1] += p[i][j] * C(i - j * k, k - 1);
      ev[i + 1][j + 1] += (ev[i][j] + p[i][j] * n * inv[n - j]) * C(i - j * k, k - 1);
    }
  }
  cout << ev[n * k][n] << endl;
}
