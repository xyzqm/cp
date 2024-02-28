#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
using namespace std;
const int N = 5e4 + 1;
const int inf = 1e9;

int n, t1, t2, d[N], p[N], in[N], out[N], tour[N];
vector<int> g[N];

struct ST {
  int n, a[4 * N];
  function<int(int, int)> f;
  function<void(int&, int)> u;

  ST(int n, decltype(f) f, decltype(u) u) : n(n), f(f), u(u) {}

  void upd(int i, int x) {
    for (u(a[i += n], x); i > 1; i >>= 1) a[i >> 1] = f(a[i], a[i ^ 1]);
  }
  int query(int l, int r) {
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = f(res, a[l++]);
      if (r & 1) res = f(res, a[--r]);
    }
    return res;
  }
};
ST lct(2 * N, [](int i, int j) { return d[i] < d[j] ? i : j; }, [](int& v, int x) { v = x; });
ST st(N, plus<int>{}, [](int& v, int x) { v += x; });

void dfs(int x = 1) {
  in[x] = t1++;
  lct.upd(tour[x] = t2++, x);
  for (int y : g[x]) if (y != p[x]) {
    d[y] = d[p[y] = x] + 1;
    dfs(y);
    lct.upd(t2++, x);
  }
  out[x] = t1;
}

int main() {
  freopen("maxflow.in", "r", stdin);
  freopen("maxflow.out", "w", stdout);
  int k; cin >> n >> k;
  for (int i = 1; i < n; i++) {
    int x, y; cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  d[0] = inf; dfs();
  while (k--) {
    int x, y; cin >> x >> y;
    if (tour[x] > tour[y]) swap(x, y);
    int lca = lct.query(tour[x], tour[y] + 1);
    st.upd(in[x], 1);
    st.upd(in[y], 1);
    st.upd(in[lca], -1);
    if (p[lca]) st.upd(in[p[lca]], -1);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) ans = max(ans, st.query(in[i], out[i]));
  cout << ans << "\n";
}
