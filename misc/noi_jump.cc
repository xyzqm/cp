// https://loj.ac/p/3159
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <vector>
#include <array>
#define int long long
#define exit(X) { cout << (X); return; }
using namespace std;
const int inf = 1e18;

template <int K>
using P = array<int, K>;
template <int K>
ostream& operator<<(ostream& os, P<K> p) {
  for (int i = 0; i < K; i++) os << p[i] << " ";
  os << endl;
  return os;
}

template <int K>
struct T { // rectangle/prism class
  P<2> a[K]{};
  T(initializer_list<P<2>> x) {
    assert(K == x.size());
    int i = 0; for (P<2> y : x) a[i++] = y;
  }
  P<2>& operator[](int i) { return a[i]; }
  bool contains(P<K> x) {
    for (int i = 0; i < K; i++) if (a[i][0] > x[i] || a[i][1] < x[i]) return false;
    return true;
  }
};

const int N = 2e5 + 1;

struct E { int t; T<2> r;
  bool operator<(const E o) const { return t > o.t; }
  E add(int x) { return {t + x, r}; }
};

template <int K>
struct KD {
  vector<P<K>> p;
  int D[4 * N]{}, d[4 * N], t[4 * N]{};
  auto cmp(int d) {
    return [=](P<K> u, P<K> v) {
        if (u[d] != v[d]) return u[d] < v[d]; 
        else return u < v;
    };
  }
  KD(vector<P<K>> _) {
    p = _;
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    queue<P<4>> q; q.push({1, 0, (int)p.size(), 0});
    fill(t, t + 4 * N, -1);
    fill(d, d + 4 * N, inf);
    fill(D, D + 4 * N, inf);
    while (q.size()) {
      auto [i, l, r, d] = q.front(); q.pop();
      if (l >= r) continue;
      int m = (l + r) >> 1;
      nth_element(p.begin() + l, p.begin() + m, p.begin() + r, cmp(d));
      t[i] = m;
      q.push({i << 1, l, m, (d + 1) % K});
      q.push({i << 1 | 1, m + 1, r, (d + 1) % K});
    }
  }
  int query(P<K> x) {
    int i = 1, d = 0;
    while (p[t[i]] != x) {
      if (cmp(d)(x, p[t[i]])) i <<= 1;
      else i = i << 1 | 1;
      d = (d + 1) % K;
      assert(t[i] >= 0);
    }
    assert(x == p[t[i]]);
    return i;
  }
  vector<int> upd(E e) { // returns a list of updated nodes
    queue<P<3>> q; q.push({1, 0, 0});  // { cur rectangle, current dimension, bitmask of edges outside current rectangle }
    vector<int> r; // updated nodes
    while (q.size()) {
      auto [i, d, m] = q.front(); q.pop();
      if (t[i] < 0) continue;
      assert(t[i] < p.size());
      P<K> x = p[t[i]];
      if (e.t >= D[i]) continue;
      if (__builtin_popcount(m) == 2 * K) D[i] = e.t;
      if (e.r.contains(x) && e.t < this->d[i]) {
        this->d[i] = e.t;
        r.push_back(i);
      }
      if (e.r[d][0] <= x[d]) q.push({i << 1, (d + 1) % K, m | (x[d] <= e.r[d][1]) * (1 << (2 * d + 1))}); // left/bottom rect
      if (e.r[d][1] >= x[d]) q.push({i << 1 | 1, (d + 1) % K, m | (x[d] >= e.r[d][0]) * (1 << (2 * d))}); // right/top rect
    }
    return r;
  }
};

vector<E> g[N];
int o[4 * N];

signed main() {
  freopen("jump.in", "r", stdin);
  freopen("jump.out", "w", stdout);
  cin.tie(0)->sync_with_stdio(0);
  int n, m, w, h; cin >> n >> m >> w >> h;
  vector<P<2>> a(n);
  for (int i = 0; i < n; i++) cin >> a[i][0] >> a[i][1];
  for (int i = 0; i < m; i++) {
    int p, t, l, r, d, u; cin >> p >> t >> l >> r >> d >> u;
    g[--p].push_back({t, {{l, r}, {d, u}}});
  }
  priority_queue<E> q;
  for (E e : g[0]) q.push(e);
  KD<2> t(a);
  for (int i = 0; i < n; i++) o[t.query(a[i])] = i;
  while (q.size()) {
    E e = q.top(); q.pop();
    for (int x : t.upd(e)) {
      for (E e_ : g[o[x]]) q.push(e_.add(e.t));
    }
  }
  for (int i = 1; i < n; i++) cout << t.d[t.query(a[i])] << endl;
}
