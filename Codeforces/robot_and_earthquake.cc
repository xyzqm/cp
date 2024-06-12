// https://codeforces.com/problemset/problem/1933/F
#include <iostream>
#include <queue>
#include <vector>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

int r;

void ac() {
  int n, m; cin >> n >> m;
  vector<vector<int>> a(n, vector<int>(m)), v(n, vector<int>(m));
  for (vector<int>& r : a) for (int& x : r) cin >> x;
  vector<vector<int>> d(n, vector<int>(m, inf));
  queue<P> q; q.push({0, 0});
  d[0][0] = 0;
  r = inf;
  while (q.size()) {
    auto [r, c] = q.front(); q.pop();
    if (c == m - 1) {
      int x = ((r - d[r][c]) % n + n) % n;
      ::r = min(::r, d[r][c] + min(n - 1 - x, x + 1));
    } else {
      if (int nr = (r + 2) % n; !a[(r + 1) % n][c] && !a[nr][c] && d[nr][c] == inf) {
        d[nr][c] = d[r][c] + 1;
        q.push({nr, c});
      }
      if (int nr = (r + 1) % n; !a[nr][c + 1] && d[nr][c + 1] == inf) {
        d[nr][c + 1] = d[r][c] + 1;
        q.push({nr, c + 1});
      }
    }
  }
  cout << (r < inf ? r : -1) << endl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int t; cin >> t;
  while (t--) ac();
}
