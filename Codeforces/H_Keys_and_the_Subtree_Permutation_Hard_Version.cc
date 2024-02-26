#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
using namespace std;
#define int long long
const int inf = 1e18;
const int N = 2e5 + 1;
int n, v[N], w[N], S[N];
vector<int> g[N];
set<int> s[N];
int dfs(int x, int p) {
  for (int y : g[x]) if (y != p) {
    dfs(y, x);
    if (s[y].size() > s[x].size()) s[x].swap(s[y]);
    s[x].insert(s[y].begin(), s[y].end());
    s[y].clear();
    S[x] += S[y];
  }
  s[x].insert(v[x]), ++S[x];
  w[x] = (s[x].size() == S[x] && *s[x].begin() == 1 && *s[x].rbegin() == S[x]);
}
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> v[i];
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1, 0);
  for (int i = 1; i <= n; i++) cout << (w[i] ? "YES\n" : "NO\n");
  return 0;
}