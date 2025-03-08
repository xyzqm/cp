#include <bits/stdc++.h>
using namespace std;
using T = tuple<int, int, int, int>;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse,sse2")
const int K = 20;
const int inf = 1e9;
int dp[2][2][K][1 << K], s[1 << K], v[2][2][K][1 << K];

int32_t main() {
  int n, m, k; cin >> n >> m >> k;
  if(k == n){
    cout << 1 << endl;
    return 0;
  }
  for (int i = 0; i < m; i++) {
    int t = 0;
    for (int j = 0; j < n; j++) {
      char c; cin >> c; 
      t |= (c == '1') * (1 << j);
    }
    s[t] = 1;
  }
  for (int k = 0; k < K; k++) {
    for (int i = 0; i < (1 << K); i++) if (!(i >> k & 1)) {
      s[i ^ (1 << k)] |= s[i];
    }
  }
  for (int t : {0, 1}) for (int j : {0, 1}) for (int k = 0; k < K; k++) fill(dp[t][j][k], dp[t][j][k] + (1 << K), inf);
  queue<T> bfs;
  bfs.push({0, 0, k, (1 << n) - 1});
  dp[0][0][k][(1 << n) - 1] = 0;
  const int all = (1 << n) - 1;
  while (bfs.size()) {
    auto [s, rm, left, t] = bfs.front(); // t[i] = 1 if its on this side
    bfs.pop();
    if (v[s][rm][left][t]) continue;
    v[s][rm][left][t] = 1;
    // cout << s << " " << t << " " << dp[s][t] << endl;
    if (s == 1 && !rm && t == (1 << n) - 1) {
      cout << dp[s][rm][left][t] << endl;
      return 0;
    }
    auto trans = [&](int a, int b, int c, int d, int del) {
      if (dp[a][b][c][d] > dp[s][rm][left][t] + del) {
        dp[a][b][c][d] = dp[s][rm][left][t] + del;
        bfs.push({a, b, c, d});
      }
    };
    if (!rm) {
      if (!::s[all ^ t]) trans(s, 1, left, t, 0); 
    } else if (left) {
      for (int i = 0; i < n; i++) if (t >> i & 1) {
        trans(s, 1, left - 1, t ^ (1 << i), 0);
      }
    }
    if (!::s[t]) trans(s ^ 1, 0, k, all ^ t, 1);
  }
  cout << -1 << endl;
}