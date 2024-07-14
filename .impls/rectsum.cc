// https://judge.yosupo.jp/problem/point_add_rectangle_sum
#include <algorithm>
#include <cassert>
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

template <int K>
struct KD {
  vector<P<K>> p;
  int V[4 * N]{}, v[4 * N]{}, t[4 * N]{};
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
    while (q.size()) {
      auto [i, l, r, d] = q.front(); q.pop();
      if (l >= r) continue;
      int m = (l + r) >> 1;
      t[i] = m;
      nth_element(p.begin() + l, p.begin() + m, p.begin() + r, cmp(d));
      q.push({i << 1, l, m, (d + 1) % K});
      q.push({i << 1 | 1, m + 1, r, (d + 1) % K});
    }
  }
  void upd(P<K> x, int w) {
    int i = 1, d = 0;
    while (p[t[i]] != x) {
      V[i] += w;
      if (cmp(d)(x, p[t[i]])) i <<= 1;
      else i = i << 1 | 1;
      d = (d + 1) % K;
      assert(t[i] >= 0);
    }
    assert(x == p[t[i]]);
    V[i] += w;
    v[i] += w;
  }
  int query(T<K> R) {
    queue<P<3>> q; q.push({1, 0, 0});  // { cur rectangle, current dimension, bitmask of edges outside current rectangle }
    int z = 0;
    while (q.size()) {
      auto [i, d, e] = q.front(); q.pop();
      if (t[i] < 0) continue;
      assert(t[i] < p.size());
      P<K> x = p[t[i]];
      if (__builtin_popcount(e) == 2 * K) { z += V[i]; continue; }
      if (R.contains(x)) z += v[i];
      if (R[d][0] <= x[d]) q.push({i << 1, (d + 1) % K, e | (x[d] <= R[d][1]) * (1 << (2 * d + 1))}); // left/bottom rect
      if (R[d][1] >= x[d]) q.push({i << 1 | 1, (d + 1) % K, e | (x[d] >= R[d][0]) * (1 << (2 * d))}); // right/top rect
    }
    return z;
  }
};

vector<P<2>> a;
vector<P<4>> q;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, Q; cin >> n >> Q;
  for (int i = 0; i < n; i++) {
    int x, y, w; cin >> x >> y >> w;
    a.push_back({x, y});
    q.push_back({-1, x, y, w});
  }
  while (Q--) {
    int t; cin >> t;
    if (t) {
      int l, d, r, u; cin >> l >> d >> r >> u;
      q.push_back({l, d, r, u});
    } else {
      int x, y, w; cin >> x >> y >> w;
      a.push_back({x, y});
      q.push_back({-1, x, y, w});
    }
  }
  KD<2> t(a);
  for (auto [a, b, c, d] : q) {
    if (a < 0) t.upd({b, c}, d);
    else cout << t.query({{{a, c - 1}, {b, d - 1}}}) << endl;
  }
}
