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

int n, a[N], q[N];
F r[N];

F m(int i, int j) { return F{a[j] - a[i], j - i}.reduce(); }

struct Q {
  int i, f, x, y;

  bool operator<(const Q& o) const {
    if (y != o.y) return y < o.y;
    else return i < o.i;
  }
};

struct Convex {
  // store points in clockwise order
  vector<int> hull;
  int l = inf; // leftmost point

  bool left(int i, int j, int k) {
    if (i < 0) return false;
    assert(i >= 0 && j >= 0 && k >= 0);
    i = hull[i], j = hull[j];
    return (a[k] - a[i]) * (j - i) - (a[j] - a[i]) * (k - i) >= 0;
  }

  void add(int i) {
    // cout << "adding " << i << endl;
    while (left(hull.size() - 2, hull.size() - 1, i)) hull.pop_back();
    if (!hull.size() || a[i] > a[hull.back()]) hull.push_back(i);
    if (l >= hull.size() || i < hull[l]) l = i;
    // cout << "added" << endl;
  }

  F query(Q q) {
    // cout << "querying " << q.i << " " << q.x << " " << q.y << endl;
    // cout << "l: " << l << endl;
    // for (int x : hull) cout << x << " ";
    // cout << endl;
    assert(q.i >= 0);
    int x = hull.size();
    for (int dif = hull.size(); dif > 0; dif /= 2) {
      while (x - dif >= l && hull[x - dif] > q.x) x -= dif;
    }
    int y = 0;
    for (int dif = hull.size(); dif > 0; dif /= 2) {
      while (y + dif <= l && hull[y + dif] > q.x) y += dif;
    }
    ++y;
    for (int dif = hull.size(); dif > 0; dif /= 2) {
      while (y + dif < x && hull[y + dif] <= q.y && !left(y + dif - 1, y + dif, q.i)) y += dif;
    }
    // cout << y << " " << m(hull[y], q.i).str() << endl;
    if (y >= 0 && y < hull.size() && a[hull[y]] <= q.y && hull[y] <= q.x && !left(y - 1, y, q.i)) return m(hull[y], q.i);
    else return {1, 0};
  }
} hull;

int main() {
  freopen("falling.in", "r", stdin);
  freopen("falling.out", "w", stdout);
  cin >> n;
  vector<Q> qs;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    qs.push_back({-1, i, i, a[i]});
  }
  for (int i = 0; i < n; i++) {
    cin >> q[i];
    --q[i], r[i] = {1, 0};
  }
  for (int i = 0; i < n; i++) {
    // cout << i << " " << q[i] << " " << a[i] << " " << a[q[i]] << endl;
    // case 1: up-right
    if (i < q[i] && a[i] <= a[q[i]]) {
      // for (int j = 0; j <= i; j++) if (a[j] <= a[i]) {
      //   r[i] = min(r[i], m(j, q[i]));
      // }
      qs.push_back({q[i], i, i, a[i]});
    }
    // case 2: down-left
    else if (q[i] < i && a[q[i]] <= a[i]) {
      r[i] = m(q[i], i);
      for (int j = i; ++j < n; ) if (a[j] > a[i]) {
        r[i] = min(r[i], m(q[i], j));
      }
    }
    // case 3: down-right
    else if (i < q[i] && a[i] > a[q[i]]) {
      for (int j = q[i]; ++j < n; ) if (a[j] > a[i]) {
        r[i] = min(r[i], m(q[i], j));
      }
    }
    // case 4: up-left
    else if (q[i] < i && a[q[i]] > a[i]) {
      // for (int j = 0; j < q[i]; j++) if (a[j] < a[i]) {
      //   r[i] = min(r[i], m(j, q[i]));
      // }
      qs.push_back({q[i], i, q[i], a[i]});
    }
    else assert(false);
  }
  sort(qs.begin(), qs.end());
  for (Q ev : qs) {
    if (ev.i < 0) hull.add(ev.f);
    else r[ev.f] = min(r[ev.f], hull.query(ev));
  }
  for (int i = 0; i < n; i++) cout << (r[i].d ? r[i].str() : "-1") << "\n";
}
