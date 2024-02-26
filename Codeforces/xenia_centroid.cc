#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1e5 + 1;
const int inf = 1e9;

int n, sz[N], up[N], red[N];
vector<int> g[N];

int dfs(int x = 1, int p = 0) {
  for (int y : g[x]) if (y != p) sz[x] += dfs(y, x);
  return ++sz[x];
}

int decompose(int x = 1, int p = 0, int n = dfs()) {
  for (int y : g[x]) if (y != p) {
    if (sz[y] > n / 2) return decompose(y, x, n);
  }
  for(int y : g[x]) {
    g[y].erase(find(g[y].begin(), g[y].end(), x));
    up[decompose(y, 0, dfs(y))] = x;
  }
  return x;
}

void upd(int x) {
  int d = 0;
  for (; x; x = up[x]) red[x] = min(red[x], d++);
}

int query(int x) {
  int d = 0, ans = inf;
  for (; x; x = up[x]) ans = min(ans, red[x] + d++);
  return ans == inf ? -1 : ans;
}

int main() {
  fill(red, red + N, inf);
  int q; cin >> n >> q;
  for (int i = 1; i < n; i++) {
    int x, y; cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  decompose(); upd(1);
  while (q--) {
    int t, x; cin >> t >> x;
    if (t == 1) upd(x);
    else cout << query(x) << '\n';
  }
}
