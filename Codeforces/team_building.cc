#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5, P = 7;
int n, p, k, a[N], s[N][P], order[N];
ll dp[(1 << 7)];
bool cmp(int i, int j) {
	return a[i] > a[j];
}
int main() {
	cin >> n >> p >> k;
	for (int i = 0; i < n; i++) cin >> a[i];
	iota(order, order + n, 0); sort(order, order + n, cmp);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) cin >> s[i][j];
	}
	fill(dp, dp + (1 << p), -1); // impossible to reach these states
	dp[0] = 0;
	for (int ind = 0; ind < n; ind++) {
		int i = order[ind];
		for (int j = (1 << p) - 1; j >= 0; j--) {
			if (dp[j] < 0) continue;
			for (int k = 0; k < p; k++) {
				if (j & (1 << k)) continue; // spot already taken
				dp[j | (1 << k)] = max(dp[j | (1 << k)], dp[j] + s[i][k]);
			}
			int cur_audience = ind - __builtin_popcount(j);
			if (cur_audience < k) dp[j] += a[i]; // assign ith person to audience
		}
	}
	cout << dp[(1 << p) - 1];
}
