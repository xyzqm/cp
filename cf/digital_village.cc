// https://codeforces.com/contest/2021/problem/E3
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 1;

int p[N], s[N], r[N], mx[N];
multiset<int, greater<>> dp[N];

int f(int x) { return p[x] = (x == p[x] ? x : f(p[x])); }
bool u(int x, int y, int w) {
	x = f(x), y = f(y);
	if (x == y) return false;
	if (s[x] < s[y]) swap(x, y);
	auto fix = [&](int x) {
		if (!dp[x].size()) dp[x].insert(mx[x] = w * r[x]);
		auto it = dp[x].begin();
		assert(w * r[x] >= mx[x]); 
		dp[x].insert(w * r[x] - mx[x] + *it);
		dp[x].erase(it);
		mx[x] = w * r[x];
	};
	fix(x), fix(y);
	for (int z : dp[y]) dp[x].insert(z);
	mx[x] += mx[y];
	p[y] = x, s[x] += s[y], r[x] += r[y];
	return true;
}

struct E { int u, v, w; 
	bool operator<(const E& o) const { return w < o.w; }
};

void ac() {
	int n, m, q; cin >> n >> m >> q;	
	for (int i = 1; i <= n; i++) {
		p[i] = i, s[i] = 1, r[i] = 0;
		dp[i].clear(), mx[i] = 0;
	}
	while (q--) {
		int x; cin >> x;
		r[x] = 1;
	}
	vector<E> g(m);
	for (E &e : g) cin >> e.u >> e.v >> e.w;
	sort(g.begin(), g.end());
	for (auto [u, v, w] : g) ::u(u, v, w);
	for (int d : dp[f(1)]) cout << (mx[f(1)] -= d) << " ";
	cout << endl;
}


signed main() {
	int t; cin >> t;
	while (t--) ac();
}

