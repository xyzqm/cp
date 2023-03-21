#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e3, K = 5e3, M = 1e9 + 7;
int s[N], c[N], dp[K + 1]; // s -> syllables, c -> rhyme
vector<int> ctw[N + 1]; // ctw[i] -> words in rhyme class i
int n, m, k; // m is lines, k is syllables
map<char, int> cnt; // how many lines per rhyme
// Algorithm:
// dp[K] -> dp[i] is ways to construct a sum of i
// dp[i] = sum(dp[i - s[j]])
int ipow(int a, int b) {
	if (!a) return 0;
	int res = 1;
	while (b) {
		if (b % 2 == 0) a = a * a % M, b /= 2;
		else res = res * a % M, b--;
	}
	return res;
}
signed main() {
	freopen("poetry.in", "r", stdin);
	freopen("poetry.out", "w", stdout);
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		cin >> s[i] >> c[i];
		ctw[c[i]].push_back((i));
	}
	for (int i = 0; i < m; i++) {
		char x; cin >> x;
		cnt[x]++;
	}
	dp[0] = 1;
	for (int i = 0; i <= k; i++) {
		for (int j = 0; j < n; j++) {
			if (i + s[j] <= k) dp[i + s[j]] += dp[i], dp[i + s[j]] %= M;
		}
	}
	int ans = 1;
	for (auto p : cnt) {
		int s1 = 0;
		for (int r = 1; r <= n; r++) {
			int s2 = 0;
			for (int w : ctw[r]) {
				s2 += dp[k - s[w]], s2 %= M;
			}
			s1 += ipow(s2, p.second), s1 %= M;
		}
		ans *= s1, ans %= M;
	}
	cout << ans;
}
