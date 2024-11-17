// https://codeforces.com/gym/104128/problem/E 
#include <cassert>
#include <iostream>
#include <set>
#include <vector>
#include <cmath>
#define int long long
using namespace std;
const int inf = 1e18;

const int N = 3e5 + 1;
const int K = 20;

vector<int> g[N];
vector<int> r[N];
int n, D, T = 0, a[N], p[N], h[N], t[N], f[N][K], st[N][K], dp[N]; 
//---SPARSE TABLE---
void build() {
  for (int i = 0; i < n; i++) st[i][0] = a[i];
  for (int k = 1; k < K; k++) for (int i = 0; i < n; i++) {
    st[i][k] = st[i][k - 1];
    if (int j = i + (1 << k - 1); j < n) st[i][k] = min(st[i][k], st[j][k - 1]);
  }
}

int mn(int l, int r) { // min on [l, r)
  int k = log2(r - l);
  return min(st[l][k], st[r - (1 << k)][k]);
}


int dfs(int x, bool i = false) {
  if (i) {
    t[x] = T++;
    r[h[x] = h[p[x]] + 1].push_back(x);
    f[x][0] = p[x];
    for (int k = 1; k < K; k++) f[x][k] = f[f[x][k - 1]][k - 1];
  }
  int s = 0;
  for (int y : g[x]) if (y != p[x]) {
    p[y] = x;
    s += dfs(y, i);
  }
  if (!i) dp[x] = min(mn(D - h[x], D - h[p[x]]), s ? s : inf);
  return dp[x];
}

int lca(int x, int y) {
  if (h[x] < h[y]) swap(x, y);
  for (int k = 0; k < K; k++) if ((h[x] - h[y]) >> k & 1) x = f[x][k];
  if (x == y) return x;
  for (int k = K; k --> 0; ) if (f[x][k] != f[y][k]) x = f[x][k], y = f[y][k];
  assert(f[x][0] == f[y][0]); return f[x][0];
}

void ac() {
  cin >> n; T = 0; h[0] = -1;
  for (int i = 1; i <= n; i++) g[i].clear(), r[i - 1].clear();
  for (int i = 0; i < n; i++) cin >> a[i];
  build();
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1, true);
  D = n;
  int x = 0;
  while (D--) if (r[D].size()) {
    auto o = [](int x, int y) { return t[x] < t[y]; };
    set<int, decltype(o)> v(o);
    for (int x : r[D]) v.insert(x);
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
      if (s.size()) g[s.back()].push_back(x);
      assert(s.size() || x == 1);
      s.push_back(x);
    }
    x += dfs(1);
  }
  cout << x << endl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int t; cin >> t;
  while (t--) ac();
}
