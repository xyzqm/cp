// https://codeforces.com/problemset/problem/1101/D
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#define int long long
#define exit(X) { cout << (X); return; }
using namespace std;
const int inf = 1e18;

const int N = 2e5 + 1;

vector<int> g[N], g_v[N], e[N], f[N];
int n, a[N], d[N], c[N], l[N];

int dfs(int v, int x, int p = 0) {
  d[x] = d[p] + 1;
  int R = x;
  l[x] = v;
  for (int y : g_v[x]) if (y != p) {
    int z = dfs(v, y, x);
    if (d[z] > d[R]) R = z;
  }
  return R;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int i = 2; i < N; i++) if (!c[i]) {
    for (int j = i; j < N; j += i) {
      f[j].push_back(i);
      if (j > i) c[j] = true;
    }
  }
  cin >> n;
  for (int i = 1; i <= n; i++) { 
    cin >> a[i];
    for (int j : f[a[i]]) e[j].push_back(i);
  }
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int r = 0;
  for (int i = 1; i < N; i++) if (!c[i]) {
    for (int u : e[i]) {
      g_v[u].clear();
      for (int v : g[u]) if (a[v] % i == 0) g_v[u].push_back(v);
    }
    for (int u : e[i]) if (l[u] < i) {
      int v = dfs(i, u);
      r = max(r, d[dfs(i, v)]);
    } 
  }
  cout << r << endl;
}
