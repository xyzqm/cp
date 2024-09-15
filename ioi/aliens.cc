#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cassert>
#ifdef ONLINE_JUDGE
#include "aliens.h"
#endif
using namespace std;
using ll = long long;

struct Line {
	mutable ll k, m, p, c;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
	ll operator()(ll x) { return k * x + m; }
	friend ostream& operator<<(ostream &os, Line l) {
    auto [k, m, p, c] = l;
    return os << k << " " << m << " " << p << " " << c << endl;
	}
};

// queries for maximums, add lines in increasing slope and increasing queries
struct MonoLine : deque<Line> {
	static const ll inf = 1e18;
	ll div(ll a, ll b) { // ceiling division
	return a / b + ((a ^ b) > 0 && a % b); }
	ll isect(Line &x, Line &y) {
		if (x.k == y.k) x.p = x.m > y.m ? inf : -inf;
		else x.p = div(y.m - x.m, x.k - y.k);
		return x.p;
	}
	void add(ll k, ll m, ll c) {
  	Line l = {k, m, inf, c};
    while (size() > 1 && isect(back(), l) < at(size() - 2).p) pop_back();
    if (!size() || isect(back(), l) < inf) push_back(l);
	}
	Line query(ll x) {
		assert(size());
		while (front().p <= x) {
      assert(front()(x) <= at(1)(x));
  		pop_front();
		}
		return front();
	}
} cht;

struct X { ll l, r;
  bool operator<(const X o) const { return l == o.l ? r < o.r : l < o.l; }
};

ll take_photos(int n, int m, int k, vector<int> r, vector<int> c) {
  swap(n, m);
  vector<X> v;
  for (int i = 0; i < m; i++) v.push_back({min(r[i], c[i]), max(r[i], c[i]) + 1});
  sort(v.begin(), v.end());
  auto ac = [&](ll L) {
    cht.clear();
    vector<ll> dp(m + 1), C(m + 1);
    ll R = 0;
    for (int i = 1; i <= m; i++) {
      auto [l, r] = v[i - 1];
      if (R >= r) dp[i] = dp[i - 1], C[i] = C[i - 1] + !L; // already completely contained
      else {
        ll o = max(0LL, R - l);
        cht.add(2 * l, -(l * l) + o * o - dp[i - 1], C[i - 1]);
        auto ln = cht.query(r);
        ll v = ln(r), c = ln.c;
        dp[i] = r * r - v + L;
        assert(dp[i] == r * r - v + L);
        C[i] = c + 1;
        assert(C[i] == c + 1);
        R = r;
      }
    }
    return make_pair(dp[m], C[m]);
  };
  ll x = (ll)n * n;
  for (ll d = x; d > 0; d /= 2) {
    while (x - d >= 0 && ac(x - d).second < k) x -= d;
  }
  --x;
  auto [y, z] = ac(x);
  return y - k * x;
}

#ifndef ONLINE_JUDGE
int main() {
  int n, m, k; cin >> n >> m >> k;
  vector<int> r(n), c(n);
  for (int i = 0; i < n; i++) cin >> r[i] >> c[i];
  cout << take_photos(n, m, k, r, c) << endl;
}
#endif
