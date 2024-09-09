#include <iomanip>
#include <ios>
#include <iostream>
#include <deque>
#include <cassert>
using namespace std;
using ld = long double;

struct Line {
	mutable ld k, m, p; int c;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ld x) const { return p < x; }
};

// queries for maximums, add lines in increasing slope and increasing queries
struct MonoLine : deque<Line> {
	const ld inf = 1/.0;
	ld div(ld a, ld b) { // floored division
		return a / b; }
	ld isect(Line &x, Line &y) {
		if (x.k == y.k) x.p = x.m > y.m ? inf : -inf;
		else x.p = div(y.m - x.m, x.k - y.k);
		return x.p;
	}
	void add(ld k, ld m, int c) {
  	Line l = {k, m, inf, c};
    while (size() > 1 && isect(back(), l) < at(size() - 2).p) pop_back();
		if (size()) isect(back(), l);
		push_back(l);
	}
	pair<ld, int> query(ld x) {
		assert(size());
		while (front().p < x) pop_front();
		auto l = front();
		return {l.k * x + l.m, l.c};
	}
} cht;

const int N = 1e5 + 1;
int n, k, cs[N];
ld dp[N];

pair<ld, int> ac(ld l) {
  cht.clear();
  cht.add(0, l, -1);
  for (int i = n; i >= 0; i--) {
    auto [v, c] = cht.query(-i);
    cht.add(1.0 / i, (dp[i] = v - l) + 1, cs[i] = (c + 1));
  }
  return {dp[0], cs[0]};
}

int main() {
  cin >> n >> k;
  ld l = 0, r = 20;
  for (ld d = r; d > 1e-13; d /= 2) {
    while (l + d < r && ac(l + d).second >= k) l += d;
  }
  auto [v, c] = ac(l);
  cout << fixed << setprecision(9) << v + k * l << endl;
}
