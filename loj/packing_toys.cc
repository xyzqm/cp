#include <cassert>
#include <iostream>
#include <set>
#define int long long
#define exit(X) { cout << (X); return; }
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 5e4 + 1;

int n, L, c[N], s[N], dp[N];

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
} ch;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> L; ++L;
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
    s[i] = s[i - 1] + ++c[i];
  }
  ch.add(0, dp[0] = 0);
  for (int i = 1; i <= n; i++) {
    dp[i] = -ch.query(s[i]) + s[i] * s[i] + L * L - 2 * L * s[i];
    ch.add(2 * s[i], -dp[i] - s[i] * s[i] - 2 * L * s[i]);
  }
  cout << dp[n] << endl;
}
