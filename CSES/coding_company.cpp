#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int M = 1e9 + 7;
const int K = 5e3;  // K is an offset to account for negatives
int n, x;     // x -> max penalty

// dp[N][N][X] -> dp[i][j][k] = first i people, j unfinished groups, k penalty
// for convenience, we 1-index dp array and 0-index person array so dp[i][j][k]
// lines up with s[i] (i.e. skill of person i + 1 = s[i])

int main() {
	cin >> n >> x;
	vector<int> s(n);
	// Notice we only need to store 2 rows!
	vector<vector<ll>> dp1(n + 1, vector<ll>(x + K + 1)); // the subarray we're currently at
	vector<vector<ll>> dp2(n + 1, vector<ll>(x + K + 1)); // the next subarray (we'll fill this up using dp1)
	for (int i = 0; i < n; i++) { cin >> s[i]; }
	sort(s.begin(), s.end());

	dp1[0][K] = 1;  // dp[0][0][0] -> 0 people, 0 unfinished groups, 0 penalty
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= (n - i); j++) {  // at most n - i unfinished groups
			for (int k = 0; k <= x + K; k++) {
				if (!dp1[j][k]) { continue; }
				dp2[j][k] += dp1[j][k];  // i has their own group
				if (j && k + s[i] <= x + K) {
					dp2[j - 1][k + s[i]] += j * dp1[j][k];  // finish group
				}
				if (j + 1 <= n - (i + 1)) {
					dp2[j + 1][k - s[i]] +=
					    dp1[j][k];  // create new unfinished group
				}
				if (j <= n - (i + 1)) {
					dp2[j][k] += j * dp1[j][k];  // extend unfinished group
				}
			}
		}
		for (int j = 0; j <= (n - (i + 1)); j++) {
			for (int k = 0; k <= x + K; k++) {
				dp1[j][k] = dp2[j][k] % M;  // i + 1 becomes the new i
				dp2[j][k] = 0;
			}
		}
	}

	int ans = 0;
	for (int i = K; i <= x + K; i++) {
		ans += dp1[0][i];
		ans %= M;
	}

	cout << ans << endl;
}