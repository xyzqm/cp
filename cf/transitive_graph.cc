// https://codeforces.com/problemset/problem/1900/E
#include <algorithm>
#include <iostream>
#include <vector>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;
 
const int N = 2e5 + 1;
 
int n, m;
vector<int> g[N], gt[N], o;
int a[N], v[N], r[N], s[N], c[N];
P p[N];
 
void reset() {
  cin >> n >> m; o.clear();
  for (int i = 1; i <= n; i++) { 
    cin >> a[i]; 
    g[i].clear(); gt[i].clear(); c[i] = s[i] = v[i] = 0; p[i] = {inf, inf};
  }
  for (int i = 1; i <= m; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v); gt[v].push_back(u);
  }
}
 
void dfs1(int x) {
  v[x] = true;
  for (int y : g[x]) if (!v[y]) dfs1(y);
  o.push_back(x);
}
 
void dfs2(int x, int r) {
  v[x] = 1; ++c[r];
  s[::r[x] = r] += a[x]; 
  for (int y : gt[x]) if (!v[y]) dfs2(y, r);
}
 
void scc() {
  for (int i = 1; i <= n; i++) if (!v[i]) dfs1(i);
  for (int i = 1; i <= n; i++) v[i] = 0;
  reverse(o.begin(), o.end());
  for (int i : o) if (!v[i]) dfs2(i, i);
  for (int i = 1; i <= n; i++) if (i == r[i]) p[i] = {n - c[i], s[i]};
}
 
void ac() {
  reset();
  scc();
  reverse(o.begin(), o.end());
  P d = {inf, inf}; for (int i = 1; i <= n; i++) d = min(d, p[r[i]]);
  for (int x : o) for (int y : g[x]) if (r[y] != r[x]) {
    P z = p[r[y]]; 
    d = min(d, p[r[x]] = min(p[r[x]], {z.first - c[r[x]], z.second + s[r[x]]}));
  } 
  cout << n - d.first << " " << d.second << endl;
}
 
signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int t; cin >> t;
  while (t--) ac();
}
