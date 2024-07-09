// https://loj.ac/p/2874 
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#define int long long
#define exit(X) { cout << (X); return; }
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e5 + 1;
const int B = 310;

int n, m, a[N], v[N], r[N];
P t[N];

struct T {
  int f[N]{};
  vector<int> s, e;
  int upd(int i) {
    e.push_back(a[i]);
    s.push_back(max((s.size() ? s.back() : 0), ++f[a[i]] * v[a[i]]));
    return s.back();
  }
  void rb() {
    assert(s.size() && e.size());
    s.pop_back();
    --f[e.back()]; e.pop_back();
  }
};

struct Q {
  int l, r, i;
  bool operator<(const Q o) const {
    if (l / B != o.l / B) return l / B < o.l / B;
    else return r < o.r;
  }
} q[N];

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  // coordinate compress
  for (int i = 0; i < n; i++) cin >> t[t[i].second = i].first;
  sort(t, t + n);
  int s = 0; for (int i = 0; i < n; i++) {
    v[a[t[i].second] = s] = t[i].first;
    if (i + 1 < n && t[i + 1].first != t[i].first) ++s;
  }
  // input queries
  for (int i = 0; i < m; i++) { cin >> q[i].l >> q[i].r; --q[i].l, --q[i].r, q[i].i = i; }
  sort(q, q + m);
  // rollback mo's
  T t;
  for (int i = 0; i < m; i++) {
    auto [l, r, I] = q[i];
    int b = l / B * B + B;
    int p = b;
    if (i && l / B != q[i - 1].l / B) while (t.s.size()) t.rb(); // changing blocks
    else if (i) p = max(q[i - 1].r, b);
    while (++p <= r) t.upd(p);
    for (int j = l; j <= min(r, b); j++) ::r[I] = t.upd(j);
    for (int j = l; j <= min(r, b); j++) t.rb();
  }
  for (int i = 0; i < m; i++) cout << r[i] << endl;
}
