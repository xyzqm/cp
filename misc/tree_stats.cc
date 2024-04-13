// https://loj.ac/p/10138
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// --constants--
const int N = 3e4 + 1;
const int inf = 1e9;

// --globals--
int n;

// --segment tree--
struct T {
  int s, m;
  T operator+(T o) {
    return {s + o.s, max(m, o.m)};
  }
  T operator+=(T o) { return *this = *this + o; }
} st[4 * N];

void upd(int i, int x, int p = 1, int l = 1, int r = n) {
  if (l == r) st[p] = {x, x};
  else {
    int m = (l + r) >> 1;
    if (i <= m) upd(i, x, p << 1, l, m);
    else upd(i, x, p << 1|1, m + 1, r);
    st[p] = st[p << 1] + st[p <<1|1];
  }
}

T query(int i, int j, int p = 1, int l = 1, int r = n) {
  if (i <= l && r <= j) return st[p];
  else if (l > j || i > r) return {0, -inf};
  else {
    int m = (l + r) >> 1;
    return query(i, j, p << 1, l, m) + query(i, j, p << 1|1, m + 1, r);
  }
}

// --heavy-light decomposition--
int t, d[N], p[N], sz[N], id[N], hv[N];
vector<int> g[N];

int dfs(int x = 1, int p = 0) {
  d[x] = d[::p[x] = p] + 1;
  if (p) g[x].erase(find(g[x].begin(), g[x].end(), p));
  for (int y : g[x]) sz[x] += dfs(y, x);
  return ++sz[x];
}

void hld(int x = hv[1] = 1) {
  st[id[x] = ++t] = {0, -inf};
  sort(g[x].begin(), g[x].end(), [&](int i, int j) { return sz[i] > sz[j]; });
  for (int y : g[x]) {
    hv[y] = (y == g[x][0] ? hv[x] : y);
    hld(y);
  }
}

T path(int x, int y) {
  T r = {0, -inf};
  while (hv[x] != hv[y]) {
    // cout << x << " " << y << "\n";
    if (d[hv[x]] > d[hv[y]]) swap(x, y);
    r += query(id[hv[y]], id[y]);
    y = p[hv[y]];
  }
  // cout << x << " " << y << "\n";
  if (id[x] > id[y]) swap(x, y);
  return r + query(id[x], id[y]);
}

// --main--
int main() {
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(); hld();
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    upd(id[i], x);
  }
  int q; cin >> q;
  while (q--) {
    string s; int a, b;
    cin >> s >> a >> b;
    if (s[0] == 'Q') {
      T r = path(a, b);
      if (s[1] == 'M') cout << r.m << "\n";
      else cout << r.s << "\n";
    } else {
      upd(id[a], b);
    }
  }
}
