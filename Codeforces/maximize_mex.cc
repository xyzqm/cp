// https://codeforces.com/contest/1139/problem/E
#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;
 
const int N = 5e3 + 1;
 
int n, m, t, c[N], p[N], k[2 * N], v[2 * N], e[N];
vector<int> g[2 * N];
 
bool dfs(int x) {
  if (v[x]) return false;
  v[x] = true;
  for (int y : g[x]) if (y <= N + t && k[y] <= N + t) {
    if (!k[y] || dfs(k[y])) {
      k[y] = x; k[x] = y;
      return true;
    }
  }
  return false;
}
 
bool kuhn(int x) {
  for (int i = 0; i < 2 * N; i++) v[i] = false;
  return dfs(x);
}
 
signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> p[i];
  for (int i = 1; i <= n; i++) cin >> c[i];
  int q; cin >> q;
  vector<int> Q(q);
  for (int &x : Q) { cin >> x; e[x] = true; }
  for (int i = 1; i <= n; i++) if (!e[i]) {
    g[c[i]].push_back(N + p[i]);
    g[N + p[i]].push_back(c[i]);
  }
  while (kuhn(N + t)) ++t;
  vector<int> r;
  while (Q.size()) {
    r.push_back(t);
    int x = Q.back(); Q.pop_back();
    g[c[x]].push_back(N + p[x]);
    g[N + p[x]].push_back(c[x]);
    while (kuhn(N + t)) ++t;
  }
  reverse(r.begin(), r.end());
  for (int x : r) cout << x << endl;
}
