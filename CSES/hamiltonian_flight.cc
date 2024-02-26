#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
using ll = long long;
const int N = 20, M = 1e9 + 7;
int n, m;
ll dp[(1 << N)][N]; // 0-indexed
vector<int> adj[N];
// dp[i][j] -> i is bitmask of what we've visited, j is current node
// transition (k is adj to j): dp[i | (1 << k)][k]
// base case: dp[(1 << i)][i] = 1
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
	}
	dp[1][0] = 1;
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			for (int k : adj[j]) {
				if (!dp[i][j] || (i & (1 << k))) continue; 
				// either it's not possible to get to this state
				// or we've already visited k
				dp[i | (1 << k)][k] += dp[i][j];
				dp[i | (1 << k)][k] %= M;
			}
		}
	}
	cout << dp[(1 << n) - 1][n - 1];
}
