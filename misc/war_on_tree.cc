//https://loj.ac/p/3789 
#include <cassert>
#include <iostream>
#include <set>
#include <vector>
#define int long long
using namespace std;
const int inf = 1e18;

const int N = 3e5 + 1;
const int K = 20;

struct E { int y, w; };
vector<E> g[N];
int n, T = 0, p[N], l[N], h[N], t[N], f[N][K], d[N][K], dp[N]; 

auto o = [](int x, int y) { return t[x] < t[y]; };
set<int, decltype(o)> v(o);

int dfs(int x, bool i = false) {
  if (!p[x]) l[x] = inf;
  if (i) {
    t[x] = T++, h[x] = h[p[x]] + 1;
    f[x][0] = p[x], d[x][0] = l[x];
    for (int k = 1; k < K; k++) {
      f[x][k] = f[f[x][k - 1]][k - 1];
      d[x][k] = min(d[x][k - 1], d[f[x][k - 1]][k - 1]);
    }
  }
  int s = 0;
  for (auto [y, w] : g[x]) if (y != p[x]) {
    p[y] = x, l[y] = w;
    s += dfs(y, i);
  }
  dp[x] = min(l[x], v.count(x) ? inf : s);
  return dp[x];
}

int lca(int x, int y) {
  if (h[x] < h[y]) swap(x, y);
  for (int k = 0; k < K; k++) if ((h[x] - h[y]) >> k & 1) x = f[x][k];
  if (x == y) return x;
  for (int k = K; k --> 0; ) if (f[x][k] != f[y][k]) x = f[x][k], y = f[y][k];
  assert(f[x][0] == f[y][0]); return f[x][0];
}

int w(int x, int y) { // from x to y
  assert(h[x] > h[y] && lca(x, y) == y);
  int r = inf;
  for (int k = 0; k < K; k++) if ((h[x] - h[y]) >> k & 1) {
    r = min(r, d[x][k]);
    x = f[x][k];
  }
  assert(x == y);
  return r;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v, w; cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }
  for (int i = 0; i < K; i++) d[0][i] = inf;
  dfs(1, true);
  int m; cin >> m;
  while (m--) {
    int k; cin >> k;
    v.clear();
    while (k--) { int x; cin >> x; v.insert(x); }
    auto t = v;
    int p = 1;
    for (int x : v) {
      t.insert(lca(p, x));
      p = x;
    }
    vector<int> s;
    for (int x : t) {
      g[x].clear();
      while (s.size() && lca(s.back(), x) != s.back()) s.pop_back();
      if (s.size()) g[s.back()].push_back({x, w(x, s.back())});
      assert(s.size() || x == 1);
      s.push_back(x);
    }
    cout << dfs(1) << endl;
  }
}
