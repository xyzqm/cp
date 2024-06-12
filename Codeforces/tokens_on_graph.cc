// https://codeforces.com/problemset/problem/1790/G
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#define int long long
#define exit(X) { cout << (X); return; }
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 2e5 + 1;

bool t[N], b[N], e[N];
int n, d[N], s[N], p[N];
vector<int> g[N];

void ac() {
  int m; cin >> n >> m;
  fill(t, t + n + 1, 0);
  fill(b, b + n + 1, 0);
  fill(e, e + n + 1, 0);
  for (int i = 1; i <= n; i++) g[i].clear();
  int T, B; cin >> T >> B; 
  while (T--) { int x; cin >> x; t[x] = true; }
  while (B--) { int x; cin >> x; b[x] = true; }
  while (m--) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
    if (b[u] && b[v]) e[u] = e[v] = true;
  }
  fill(d, d + n + 1, inf); d[1] = 0;
  queue<int> q; q.push(1);
  while (q.size()) {
    int x = q.front(); q.pop();
    for (int y : g[x]) if (d[y] == inf) {
      d[y] = d[x] + 1;
      if (b[y]) q.push(y);
    }
  }
  int z = 0; for (int i = 1; i <= n; i++) if (t[i]) { 
    if (d[i] < d[z]) z = i;
  }
  if (!z) exit("NO\n");
  int x = 0;
  for (int i = 1; i <= n; i++) if (t[i] && i != z) {
    int y = 0;
    for (int j : g[i]) {
      if (e[j]) exit("YES\n");
      if (b[j]) y = 1;
    } 
    x += y;
  }
  exit(x + 1 >= d[z] ? "YES\n" : "NO\n");
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int t; cin >> t;
  while (t--) ac();
}


