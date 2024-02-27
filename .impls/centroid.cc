#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
using P = pair<int, int>;
const int N = 1e5 + 1;
const int inf = 1e9;

int n, sz[N], red[N];
set<int> g[N];
vector<P> up[N];

int dfs(int x = 1, int p = 0) {
  sz[x] = 0;
  for (int y : g[x]) if (y != p) sz[x] += dfs(y, x);
  return ++sz[x];
}

void push(int centroid, int x, int p = 0, int d = 1) {
  for (int y : g[x]) if (y != p) {
    push(centroid, y, x, d + 1);
  }
  up[x].push_back({centroid, d});
}

int decompose(int x = 1, int p = 0, int n = dfs()) {
  for (int y : g[x]) if (y != p) {
    if (sz[y] > n / 2) return decompose(y, x, n);
  }
  for(int y : g[x]) {
    g[y].erase(x);
    push(x, y);
    decompose(y, x, dfs(y));
  }
  g[x].clear();
  up[x].push_back({x, 0});
  return x;
}

void upd(int x) {
  for (auto [u, d] : up[x]) red[u] = min(red[u], d);
}

int query(int x) {
  int ans = inf;
  for (auto [u, d] : up[x]) ans = min(ans, red[u] + d);
  return ans == inf ? -1 : ans;
}

int main() {
  fill(red, red + N, inf);
  int q; cin >> n >> q;
  for (int i = 1; i < n; i++) {
    int x, y; cin >> x >> y;
    g[x].insert(y);
    g[y].insert(x);
  }
  decompose(); upd(1);
  while (q--) {
    int t, x; cin >> t >> x;
    if (t == 1) upd(x);
    else cout << query(x) << '\n';
  }
}
