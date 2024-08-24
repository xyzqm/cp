// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
#define int long long
using namespace std;
using P = pair<int, int>;

const int inf = 1e18;
const int N = 2e5 + 1;
const int K = 20;

struct ST {
	bool mn;
	int st[N + 1][K]{};
	int f(int x, int y) {
		if (x < y) return mn ? x : y;
		else return mn ? y : x;
	}
	//---SPARSE TABLE---
	void build(vector<int> &a, bool m) { // m -> whether to use min(true) or max(false)
		mn = m;
		int n = a.size();
		for (int i = 0; i < n; i++) st[i][0] = a[i];
		for (int k = 1; k < K; k++) for (int i = 0; i < n; i++) {
			st[i][k] = st[i][k - 1];
			if (int j = i + (1 << k - 1); j < n) st[i][k] = f(st[i][k], st[j][k - 1]);
		}
	}
	int F(int l, int r) { // min on [l, r)
	if (l == r) return mn ? inf : -inf;
	int k = log2(r - l);
	return f(st[l][k], st[r - (1 << k)][k]);
	}
} A, B;


void ac() {
	int n; cin >> n;
	vector<int> a(n), b(n);
	for (int &x : a) cin >> x;
	for (int &x : b) cin >> x;
	A.build(a, false);
	B.build(b, true);
	for (int i = 0; i < n; i++) {
		int j1 = i, j2 = i; // j1 for a, j2 for b
		for (int d = n; d > 0; d /= 2) {
			while (j1 + d <= n && A.F(i, j1 + d) <= b[i]) j1 += d;
		}
		for (int d = n; d > 0; d /= 2) {
			while (j2 + d <= n && B.F(i, j2 + d) >= b[i]) j2 += d;
		}
		// cout << i << " " << j1 << " " << j2 << endl;
		if (A.F(i, min(j1, j2)) == b[i]) continue;
		j1 = i, j2 = i; // j1 for a, j2 for b
		for (int d = n; d > 0; d /= 2) {
			while (j1 - d >= 0 && A.F(j1 - d, i + 1) <= b[i]) j1 -= d;
		}
		for (int d = n; d > 0; d /= 2) {
			while (j2 - d >= 0 && B.F(j2 - d, i + 1) >= b[i]) j2 -= d;
		}
		if (A.F(max(j1, j2), i + 1) == b[i]) continue;
		cout << "NO" << endl;
		return;
	}
	cout << "YES" << endl;

}

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	int t; cin >> t;
	while (t--) ac();

}
