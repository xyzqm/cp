#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int c2(int v) { return v * (v - 1) / 2; }

const int inf = 1e18;

// KACTL LineContainer
struct Line {
  mutable int k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(int x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  int div(int a, int b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(int k, int m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  int query(int x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    int mn = c2(n); // min pairs to subtract off
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // dp[u] = min subtracted considering nodes in u's subtree
    // + assuming that u is connected to its parent
    vector<int> dp(n + 1, 0), sz(n + 1, 1);
    [&](this auto &&dfs, int x, int p) -> void {
        for (int y : g[x]) if (y != p) {
            dfs(y, x);
            sz[x] += sz[y];
        }
        dp[x] = c2(sz[x]);
        for (int y : g[x]) if (y != p) dp[x] = min(dp[x], dp[y] + c2(sz[x] - sz[y]));
    }(1, 0);
    [&](this auto &&upd, int x, int p) -> void { // consider all possible lcas
        for (int y : g[x]) if (y != p) upd(y, x);
        LineContainer lc;
        lc.add(0, 0);
        for (int y : g[x]) if (y != p) {
            mn = min(mn, dp[y] + c2(n - sz[y]) - lc.query(n - sz[y]));
            lc.add(sz[y], -dp[y] + c2(sz[y]) - sz[y] * sz[y]);
        }
    }(1, 0);
    cout << 2 * c2(n) - mn << "\n";
}
