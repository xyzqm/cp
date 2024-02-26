// https://cses.fi/problemset/task/2134
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 2e5 + 1;
int n, t = 0, v[N], p[N], d[N], id[N], hv[N], sz[N], st[2 * N];
vector<int> g[N];

// segment tree
void build() {
  for (int i = n; --i > 0; ) st[i] = max(st[i << 1], st[i << 1 | 1]);
}

void upd(int i, int x) {
  for (st[i += n] = x; i > 1; i >>= 1) st[i >> 1] = max(st[i], st[i ^ 1]);
}

int query(int l, int r) {
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) res = max(res, st[l++]);
    if (r & 1) res = max(res, st[--r]);
  }
  return res;
}

// HLD
int dfs(int x = 1) {
  if (x > 1) g[x].erase(find(g[x].begin(), g[x].end(), p[x]));
  for (int &y : g[x]) {
    p[y] = x, d[y] = d[x] + 1;
    sz[x] += dfs(y);
    if (sz[y] > sz[g[x][0]]) swap(y, g[x][0]);
  }
  return ++sz[x];
}

void hld(int x = 1) {
  id[x] = t++;
  for (int y : g[x]) {
    hv[y] = (y == g[x][0] ? hv[x] : y);
    hld(y);
  }
}

int path(int x, int y) {
  int res = 0;
  for (; hv[x] != hv[y]; y = p[hv[y]]) {
    if (d[hv[x]] > d[hv[y]]) swap(x, y);
    res = max(res, query(id[hv[y]], id[y] + 1));
  }
  if (d[x] > d[y]) swap(x, y);
  return max(res, query(id[x], id[y] + 1));
}

int main() {
  int q; cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> v[i];
  for (int i = 1; i < n; i++) {
    int x, y; cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  dfs(); hld();
  for (int i = 1; i <= n; i++) st[id[i] + n] = v[i];
  build();
  while (q--) {
    int a, b; cin >> t >> a >> b;
    if (t == 1) upd(id[a], b);
    else cout << path(a, b) << "\n "[q > 0];
  }
}
