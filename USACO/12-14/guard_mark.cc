#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 20;
int n, H, h[N], w[N], s[N], dp[(1 << 20)], tw[(1 << 20)], th[(1 << 20)];
signed main() {
	freopen("guard.in", "r", stdin);
	freopen("guard.out", "w", stdout);
	cin >> n >> H;
	for (int i = 0; i < n; i++) {
		cin >> h[i] >> w[i] >> s[i];
	}
	fill(dp, dp + (1 << n), -1);
	dp[0] = LLONG_MAX, tw[0] = th[0] = 0;
	int ans = -1;
	for (int b = 0; b < (1 << n); b++) {
		if (dp[b] < 0) continue; // not possible to achieve this state
		if (th[b] >= H) ans = max(ans, dp[b]);
		for (int i = 0; i < n; i++) {
			if (b & (1 << i)) continue; // this cow has already been used
			tw[b | (1 << i)] = tw[b] + w[i];
			th[b | (1 << i)] = th[b] + h[i];
			if (tw[b] <= s[i]) { // try to put cow i on the bottom
				dp[b | (1 << i)] = max(dp[b | (1 << i)], min(dp[b], s[i] - tw[b]));
			}
		}
	}
	if (ans == -1) cout << "Mark is too tall" << endl;
	else cout << ans << endl;
}
