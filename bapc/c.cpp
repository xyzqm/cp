#include <bits/stdc++.h>
#define upd(x, y) x = max(x, (y))
using namespace std;

const int K = 22;
int e[1 << K], dp[1 << K], pos[1 << K];

int32_t main() {
  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    int y = (1 << (31 - __builtin_clz(x)));
    pos[x ^ y ^ (y - 1)] |= y;
  }
  for (int k = 0; k < K; k++) {
    for (int i = 0; i < (1 << K); i++) if (i >> k & 1) {
      pos[i ^ (1 << k)] |= pos[i];
    }
  }
  int r = 0;
  for (int i = 0; i < (1 << K); i++) {
    upd(r, dp[i]);
    for (int j = 0; j < K; j++) if (!(i >> j & 1)) {
      if (1 << j > i && (pos[i] >> j & 1)) {
        upd(dp[i ^ (1 << j)], dp[i] + 1); 
      }
    }
  }
  cout << r << endl;
}