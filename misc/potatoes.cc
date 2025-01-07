// https://codeforces.com/group/stXErQM0NN/contest/528845/problem/E
#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 2e5 + 1;
const int M = 998244353;
const int pct = 828542813;

struct mint {
	int v;
	mint(int v = 0) : v(v % M) {}
	operator int() { return v; }
};

int n;
struct F {
	mint m, b;
	mint operator()(mint x)	{ return m * x + b; }
	F operator()(F f) { return { m * f.m, m * f.b + b}; }
	F operator+(F o) { return {m + o.m, b + o.b}; }
} rt[4 * N], sum[4 * N];

ostream& operator<<(ostream &os, F f) { return os << f.m << ":" << f.b; }

void upd(int i, mint x, int p = 1, int l = 0, int r = n) {
    if (r - l == 1) rt[p] = {x, x}, sum[p] = {x, x};
    else {
        int m = (l + r) >> 1;
        if (i < m) upd(i, x, p << 1, l, m);
        else upd(i, x, p << 1 | 1, m, r);
        rt[p] = rt[p << 1 | 1](rt[p << 1]);
    	sum[p] = sum[p << 1] + sum[p << 1 | 1](rt[p << 1]);
    }
}

int32_t main() {
	int q; cin >> n >> q;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		upd(i, x * pct);
	}
	while (q--) {
		int i, x; cin >> i >> x;
		upd(--i, x * pct);
		cout << sum[1].b << endl;
	}
}
