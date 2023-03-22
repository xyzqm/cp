#include <bits/stdc++.h>
using namespace std;
const int N = 20;
set<int> showtimes[N];
int n, l, L[N], dp[(1 << N)];
// dp[s] -> max end time
int main() {
	freopen("movie.in", "r", stdin);
	freopen("movie.out", "w", stdout);
	cin >> n >> l;
	for (int i = 0; i < n; i++) {
		cin >> L[i];
		int c; cin >> c;
		for (int j = 0; j < c; j++) {
			int x; cin >> x;
			showtimes[i].insert(x);
		}
	}
	dp[0] = 0;
	int ans = INT_MAX;
	for (int s = 0; s < (1 << n); s++) {
		if (dp[s] >= l) ans = min(ans, __builtin_popcount(s));
		for (int j = 0; j < n; j++) {
			if (s & (1 << j)) continue;
			// find latest showtime that starts before current showtime ends
			auto it = showtimes[j].upper_bound(dp[s]);
			if (it == showtimes[j].begin()) continue; // all showtimes start later
			it = prev(it);
			dp[s | (1 << j)] = max(dp[s | (1 << j)], *it + L[j]);
		}
	}
	if (ans == INT_MAX) cout << -1;
	else cout << ans;
}
