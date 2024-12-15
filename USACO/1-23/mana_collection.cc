#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 18;
const int inf = 2e18;
int dp[1 << N][N]; // mask of current visited points + ending point
int n, g[N][N], m[N], sum[1 << N];

struct Line {
  mutable int k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(int x) const { return p < x; }
};

// queries for maximums
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
} lc[N];

signed main() {
    int e; cin >> n >> e;
    for (int i = 0; i < n; i++) cin >> m[i];
    for (int i = 1; i < (1 << n); i++) {
        sum[i] = sum[i - (i & -i)] + m[__builtin_ctzll(i)];
    }
    while (e--) {
        int u, v, w; cin >> u >> v >> w;
        g[--v][--u] = w; // store reverse edges
    }
    // run a floyd-warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) if (g[i][k]) {
            for (int j = 0; j < n; j++) if (g[k][j]) {
                if (!g[i][j]) g[i][j] = inf; // NOTE: INIT FLOYD WARSHALL
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) if (!(i >> j & 1)) {
            dp[i][j] = i ? inf : 0;
            for (int k = 0; k < n; k++) if (g[j][k] && i >> k & 1) {
                dp[i][j] = min(dp[i][j], dp[i ^ (1 << k)][k] + sum[i] * g[j][k]);
            }
            lc[j].add(sum[i | (1 << j)], -dp[i][j]);
        }
    }
    int t; cin >> t;
    while (t--) {
        int s, e; cin >> s >> e;
        cout << lc[--e].query(s) << endl;
    }
}
