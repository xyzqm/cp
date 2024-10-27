#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
#define int long long
const int inf = 1e18;
const int N = 1e5 + 1;
set<int> g[N];
bool v[N];
int s[N], p[N];
int P(int x) { return p[x] = p[x] == x ? x : P(p[x]); }
int U(int x, int y) {
  x = P(x), y = P(y);
  if (x == y) return 0;
  if (s[x] < s[y]) swap(x, y);
  p[y] = x;
  s[x] += s[y];
  return 1;
}
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i <= n; i++) s[i] = 1, p[i] = i;
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    g[u].insert(v);
    g[v].insert(u);
  }
  for (int i = 1; i <= n; i++) {
    if (g[i].size() < n / 2) U(0, i);
    else {
      for (int j = 1; j <= n; j++) {
        if (g[i].find(j) == g[i].end()) U(i, j);
      }
    }
  }
  set<int> r;
  for (int i = 1; i <= n; i++) r.insert(P(i));
  cout << r.size() - 1 << endl;
  return 0;
}
