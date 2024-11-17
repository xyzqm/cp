#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cassert>
using namespace std;
#define int long long
#define u first
#define v second
const int inf = 1e18;
using P = pair<int, int>;
int C2(int n) { return n * (n - 1) / 2; }
vector<vector<int>> g;
vector<bool> v;
int x = inf, c = 0;
void dfs(int u) {
  ++c;
  x = min(x, (int)g[u].size());
  for (int y : g[u]) if (!v[y]) {v[y] = true, dfs(y);}
}
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int t; cin >> t;
  while (t--) {
    int on, n, m, k;
    cin >> n >> m >> k;
    on = n;
    int K = k;
    k = min(k, 20LL);
    vector<P> E(m);
    g.assign(n, vector<int>());
    for (int i = 0; i < m; i++) {
      cin >> E[i].u >> E[i].v;
      --E[i].u, --E[i].v;
      g[E[i].u].push_back(i);
      g[E[i].v].push_back(i);
    }
    int r = inf;
    int last = -inf, cur = n;
    while (k--) {
      r = min(r, n);
      n = m;
      m = 0;
      for (vector<int>& v : g) m += C2((int)v.size());
      if (m > 2 * on) {
        if (k) r = min(r, n); 
        break;
      }
      vector<vector<int>> G(n);
      vector<P> e;
      for (int i = 0; i < E.size(); i++) {
        for (int j : g[E[i].u]) if (i < j) e.push_back({i, j});
        for (int j : g[E[i].v]) if (i < j) e.push_back({i, j});
      }
      assert(e.size() == m);
      for (int i = 0; i < e.size(); i++) {
        G[e[i].u].push_back(i);
        G[e[i].v].push_back(i);
      }
      E = e;
      g = G;
      last = cur, cur = n;
    }
    k = min(K, 20LL);
    if (--K >= k && cur < last && m <= 2 * on) {
      r = n;
      v.assign(n, 0);
      for (int i = 0; i < n; i++) {
        for (int& x : g[i]) x = (E[x].u == i ? E[x].v : E[x].u);
      }
      for (int i = 0; i < n; i++) if (!v[i]) {
        x = inf, c = 0;
        v[i] = true, dfs(i);
        if (x < 2) r -= min(K - k, c);
      }
    }
    cout << r << endl;
  }
  return 0;
}