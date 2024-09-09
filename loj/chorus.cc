#include <deque>
#include <iostream>
#include <cassert>
#include <numeric>
#include <string>
#include <vector>
#include <set>
using ll = long long;
using namespace std;

struct Line {
	mutable ll k, m, p, c;
	bool operator<(const Line& o) const { return k == o.k ? c > o.c : k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

const int N = 1e6 + 1;

// queries for maximums
struct MonoLine : deque<Line> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = 1e18;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	int isect(Line &x, Line &y) {
		if (x.k == y.k) x.p = x.m > y.m ? inf : -inf;
		else x.p = div(y.m - x.m, x.k - y.k);
		return x.p;
	}
	void add(ll k, ll m, ll c) {
  	Line l = {k, m, inf, c};
    while (size() > 1 && isect(back(), l) < at(size() - 2).p) pop_back();
		if (size()) isect(back(), l);
		push_back(l);
	}
	pair<ll, ll> query(ll x) {
		assert(size());
		while (front().p < x) pop_front();
		auto l = front();
		return {l.k * x + l.m, l.c};
	}
} cht;

int n, k, r[N];
ll dp[N], cs[N], f[N], u[N + 1], t[N];
vector<ll> ys(1);

pair<ll, ll> ac(ll l) {
  cht.clear();
  cht.add(0, 0, 0);
  for (int i = 1; i <= n; i++) {
    auto [v, c] = cht.query(i);
    dp[i] = t[i] - v + l;
    cht.add(i, u[i] - dp[i] - (ll)i * r[i], (cs[i] = c + 1));
  }
  return {dp[n], cs[n]};
}

int main() {
  cin >> n >> k;
  string s; cin >> s;
  int y = 0;
  for (char c : s) {
    if (c == 'A') {
      ys.push_back(y);
      f[y] += y;
    } else r[++y] = ys.size() - 1;
  }
  partial_sum(f, f + n, u + 1); // u[i]: area within y[0, i)
  partial_sum(ys.begin(), ys.end(), t); // t[i]: area within x[0, i]
  for (int i = 1; i <= n; i++) {
    u[i] = max(u[i], t[i]);
    r[i] = max(r[i], i);
  }
  ll l = -1, r = 1e12;
  for (ll d = r; d > 0; d /= 2) {
    while (l + d <= r && ac(l + d).second > k) l += d;
  }
  auto [v, c] = ac(++l);
  cout << v - l * k << endl;
}
