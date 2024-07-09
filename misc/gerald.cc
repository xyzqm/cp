// https://www.codechef.com/problems/GERALD07
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;
const int inf = 1e18;

const int N = 2e5 + 1;
const int B = 440;
struct E { int u, v; } e[N];
int n, r[N];

struct T {
  int s[N], p[N], cc = n;
  T() { for (int i = 1; i <= n; i++) s[i] = 1, p[i] = i; }
  vector<int> h; // history
  int r(int u) { return u == p[u] ? u : r(p[u]); }
  int upd(int i) {
    auto [u, v] = e[i];
    u = r(u), v = r(v);
    if (u == v) {
      h.push_back(0); // no-op
      return cc;
    }
    if (s[u] > s[v]) swap(u, v); // we want to unite u to v
    h.push_back(u);
    p[u] = v, s[v] += s[u];
    return --cc;
  }
  int rb() {
    assert(h.size());
    int u = h.back(); h.pop_back();
    if (!u) return cc;
    else return s[p[u]] -= s[u], p[u] = u, ++cc;
  }
};

struct Q {
  int l, r, i;
  bool operator<(const Q o) const {
    if (l / B != o.l / B) return l / B < o.l / B;
    else return r < o.r;
  }
} q[N];

void ac() {
  int m, Q; cin >> n >> m >> Q;
  for (int i = 1; i <= m; i++) cin >> e[i].u >> e[i].v;
  for (int i = 0; i < Q; q[i].i = i, i++) cin >> q[i].l >> q[i].r;
  sort(q, q + Q);
  T t;
  for (int i = 0; i < Q; i++) {
    auto [l, r, I] = q[i];
    int b = l / B * B + B;
    int p = b;
    if (i && l / B != q[i - 1].l / B) while (t.h.size()) ::r[I] = t.rb(); // changing blocks
    else if (i) p = max(q[i - 1].r, b);
    while (++p <= r) ::r[I] = t.upd(p);
    for (int j = l; j <= min(r, b); j++) ::r[I] = t.upd(j);
    for (int j = l; j <= min(r, b); j++) t.rb();
  }
  for (int i = 0; i < Q; i++) cout << r[i] << endl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int t; cin >> t;
  while (t--) ac();
}
