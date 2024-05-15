// https://codeforces.com/problemset/problem/1921/G
#include <algorithm>
#include <iostream>
#include <vector>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e5 + 1;

vector<vector<int>> v(int n, int m) { return vector<vector<int>>(n, vector<int>(m)); }

int n, m, k;

int ak(vector<vector<int>> a) {
  int n = a.size(), m = a[0].size();
  auto pr = v(n, m), pc = v(n, m), d = v(n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      d[i][j] = a[i][j] + (i && j < m - 1 ? d[i - 1][j + 1] : 0);
      pr[i][j] = a[i][j] + (j ? pr[i][j - 1] : 0);
      pc[i][j] = a[i][j] + (i ? pc[i - 1][j] : 0);
    }
  }
  auto c = [&](int i, int j) {
    if (i < n && j < m) return d[i][j];
    if (i + j >= n + m - 1) return 0LL;
    if (i >= n) return d[n - 1][i + j - n + 1];
    return 0LL;
  };
  auto r = v(n, m);
  for (int i = 0; i <= min(n + m, k); i++) r[0][0] += c(i, 0);
  for (int i = 1; i < n; i++) {
    r[i][0] = r[i - 1][0] - pr[i - 1][min(m - 1, k)] + c(i + k, 0) - c(i - 1, k + 1);
  } 
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < m; j++) {
      r[i][j] = r[i][j - 1] - (pc[min(n - 1, i + k)][j - 1] - (i ? pc[i - 1][j - 1] : 0))  + c(i + k, j) - (i ? c(i - 1, j + k + 1) : 0);
    }
  }
  int x = 0;
  for (auto &v : r) x = max(x, *max_element(v.begin(), v.end()));
  return x;
}

auto rotate(vector<vector<int>> &a) {
  int n = a.size(), m = a[0].size();
  auto x = v(m, n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      x[j][n - 1 - i] = a[i][j];
    }
  }
  return x;
}

void ac() {
  cin >> n >> m >> k;
  k = min(k, n + m - 1);
  auto a = v(n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char c; cin >> c;
      a[i][j] = (c == '#');
    }
  }
  int r = 0;
  for (int i = 0; i < 4; i++) r = max(r, ak(a = rotate(a)));
  cout << r << endl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int t; cin >> t;
  while (t--) ac();
}
