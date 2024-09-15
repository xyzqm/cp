#include <deque>
#include <cassert>
using namespace std;
using ll = long long;

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

// queries for maximums, add lines in increasing slope and increasing queries
struct MonoLine : deque<Line> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = 1e18;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	ll isect(Line &x, Line &y) {
		if (x.k == y.k) x.p = x.m > y.m ? inf : -inf;
		else x.p = div(y.m - x.m, x.k - y.k);
		return x.p;
	}
	void add(ll k, ll m) {
  	Line l = {k, m, inf};
    while (size() > 1 && isect(back(), l) < at(size() - 2).p) pop_back();
		if (size()) isect(back(), l);
		push_back(l);
	}
	ll query(ll x) {
		assert(size());
		while (front().p < x) pop_front();
		auto l = front();
		return l.k * x + l.m;
	}
};
