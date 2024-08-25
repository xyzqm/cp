// Source: https://usaco.guide/general/io
#include <vector>
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
};
