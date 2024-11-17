// https://codeforces.com/contest/1938/problem/E
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#define int long long
using namespace std;

const int inf = 1e18;

const int N = 1e2 + 1;
int n, a[N][N];

void solve() {
  cin >> n;
  vector<vector<int>> cr(n, vector<int>(n + 1)), cc(n, vector<int>(n + 1));
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) { cin >> a[i][j]; cr[i][j + 1] = cc[i][j + 1] = 0; }
  auto rem = [](vector<int>& v, int x) { 
    auto it = find(v.begin(), v.end(), x);
    if (it != v.end()) v.erase(it); 
  };
  vector<int> dr(n);
  iota(dr.begin(), dr.end(), 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) if (++cr[i][a[i][j]] == 2) rem(dr, i);
  }
  vector<int> dc(n);
  iota(dc.begin(), dc.end(), 0);
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < n; i++) if (++cc[j][a[i][j]] == 2) rem(dc, j); 
  }
  int m = min(dr.size(), dc.size());
  vector<tuple<int, int, int>> r; 
  for (int i = 0; i < m; i++) {
    int x = a[dr[i]][dc[i]], y = (x == n ? 1 : x + 1);
    r.push_back({dr[i], dc[i], y});
    --cr[dr[i]][x], ++cr[dr[i]][y];
    --cc[dc[i]][x], ++cc[dc[i]][y];
  }
  auto& v = (m < dr.size() ? dr : dc);
  auto &c = (m < dr.size() ? cc : cr);
  for (int _ = m; _ < v.size(); _++) {
    int i = v[_];
    if (*max_element(c[i].begin(), c[i].end()) > 2) r.push_back({i, i, a[i][i] == n ? 1 : a[i][i] + 1});
    else {
      for (int j = 1; j <= n; j++) if (j != a[i][i] && c[i][j]) { r.push_back({i, i, j}); break; }
    }
  }
  cout << r.size() << endl;
  for (auto [i, j, k] : r) {
    cout << ++i << " " << ++j << " " << k << endl;
  }
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int t; cin >> t;
  while (t--) solve();
}
