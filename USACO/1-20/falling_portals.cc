#include <cstdio>
#include <iostream>
#include <numeric>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 2e5;
const int inf = 1e9;

struct F {
  ll n, d;

  F reduce() {
    int g = gcd(n, d);
    if (g) n /= g, d/= g;
    return *this;
  }

  string str() {
    return "" + to_string(n) + "/" + to_string(d);
  }

  bool operator<(const F& o) const { return n * o.d < d * o.n; }
};

struct Q {
  int i, f, x;
  ll y;

  bool operator<(const Q& o) const {
    if (y != o.y) return y < o.y;
    else return i < o.i;
  }
};

struct Convex {
  // store points in clockwise order
  vector<int> hull;
  int n;
  int l = inf; // leftmost point
  ll a[N]; // y-coordinates
  vector<Q> q; // queries
  F r[N]; // answers for each query

  // sneaky little override >:)
  void upd(int i, ll y) {
    a[i] = y;
    q.push_back({-1, i, i, y});
  }

  // register path from (i, a[i]) to (x, a[x]) in list of queries
  void upd(int i, int x) {
    assert(a[x] >= a[i]);
    q.push_back({x, i, min(i, x), a[i]});
  }

  // get accepted :)
  void ac() {
    for (int i = 0; i < n; i++) r[i] = {1, 0};
    sort(q.begin(), q.end());
    for (Q ev : q) {
      if (ev.i < 0) add(ev.f);
      else r[ev.f] = min(r[ev.f], query(ev));
    }
  }

  F m(int i, int j) { return F{a[j] - a[i], j - i}.reduce(); }

  // whether i -> j -> k constitutes a left turn
  bool left(int i, int j, int k) {
    if (i < 0) return false;
    assert(i >= 0 && j >= 0 && k >= 0);
    i = hull[i], j = hull[j];
    return (a[k] - a[i]) * (j - i) - (a[j] - a[i]) * (k - i) >= 0;
  }

  // adds point (i, a[i]) into the hull
  void add(int i) {
    while (left(hull.size() - 2, hull.size() - 1, i)) hull.pop_back();
    if (!hull.size() || a[i] > a[hull.back()]) hull.push_back(i);
    if (l >= hull.size() || i < hull[l]) l = hull.size() - 1;
  }

  F query(Q q) {
    assert(q.i >= 0);
    int x = hull.size();
    for (int dif = hull.size(); dif > 0; dif /= 2) {
      while (x - dif >= l && hull[x - dif] > q.x) x -= dif;
    }
    int y = -1;
    for (int dif = hull.size(); dif > 0; dif /= 2) {
      while (y + dif <= l && hull[y + dif] > q.x) y += dif;
    }
    ++y;
    for (int dif = hull.size(); dif > 0; dif /= 2) {
      while (y + dif < x && !left(y + dif - 1, y + dif, q.i)) y += dif;
    }
    if (
      y >= 0 && y < hull.size()
      && a[hull[y]] <= q.y && hull[y] <= q.x
      && !left(y - 1, y, q.i)
    ) {
      return m(hull[y], q.i);
    }
    else return {1, 0};
  }
} hull, rhull;

int main() {
  freopen("falling.in", "r", stdin);
  freopen("falling.out", "w", stdout);
  int n; cin >> n;
  hull.n = rhull.n = n;
  for (int i = 0; i < n; i++) {
    ll y; cin >> y;
    hull.upd(i, y);
    rhull.upd(n - i - 1, -y);
  }
  for (int i = 0; i < n; i++) {
    int x; cin >> x; --x;
    if (hull.a[i] <= hull.a[x]) hull.upd(i, x);
    else rhull.upd(n - 1 - i, n - 1 - x);
  }
  hull.ac(); rhull.ac();
  for (int i = 0; i < n; i++) {
    F r = min(hull.r[i], rhull.r[n - 1 - i]);
    cout << (r.d ? r.str() : "-1") << "\n";
  }
}
