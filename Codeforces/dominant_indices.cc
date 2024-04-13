/**
https://codeforces.com/contest/1009/problem/F
Solution sketch:
dp[x][i] -> # of descendants a distance i from x
ans[x] -> self explanatory
dp[x] -> dp[hc_x] << 1 + sum of dp[y] << 1 where y is in lc_x
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1e6 + 1;

int n, t, r[N], d[N], id[N], dp[N];
vector<int> g[N];

void depths(int x, int p) {
  if (p) g[x].erase(find(g[x].begin(), g[x].end(), p));
  for (int y : g[x]) depths(y, x);
  d[p] = max(d[p], d[x] + 1);
}

void dfs(int x) {
  id[x] = t++;
  sort(g[x].begin(), g[x].end(), [&](int u, int v) { return d[u] > d[v]; });
  for (int y : g[x]) dfs(y);
}

void lsd(int x) {
  dp[id[x]] = 1;
  if (g[x].size()) lsd(g[x][0]);
  r[x] = g[x].size() ? r[g[x][0]] + 1 : 0;
  if (dp[id[x]] >= dp[id[x] + r[x]]) r[x] = 0;
  for (int y : g[x]) if (y != g[x][0]) {
    lsd(y);
    for (int i = 0; i <= d[y]; i++) {
      dp[id[x] + i + 1] += dp[id[y] + i];
      if (
        dp[id[x] + i + 1] > dp[id[x] + r[x]] ||
        (dp[id[x] + i + 1] == dp[id[x] + r[x]] && i + 1 < r[x])
      )
        r[x] = i + 1;
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  depths(1, 0); dfs(1); lsd(1);
  for (int i = 1; i <= n; i++) cout << r[i] << "\n";
}
