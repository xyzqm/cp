#include <bits/stdc++.h>
using namespace std;
bool seen[256];
int adj[256][256];
int dp[1 << 20];
int main() {
	string s; cin >> s;
	vector<char> letters;
	for (int i = 0; i < s.length(); i++) {
		if (!seen[s[i]]) {
			letters.push_back(s[i]);
			seen[s[i]] = true;
		}
		if (i) adj[s[i - 1]][s[i]]++;
	}
	int l = letters.size();
	fill(dp, dp + (1 << l), INT_MAX);
	dp[0] = 1;
	for (int s = 0; s < (1 << l); s++) {
		for (int i = 0; i < l; i++) {
			if (s & (1 << i)) continue;
			int new_state = dp[s];
			for (int j = 0; j < l; j++) {
				if (!(s & (1 << j))) continue;
				new_state += adj[letters[i]][letters[j]];	
			}
			dp[s | (1 << i)] = min(dp[s | (1 << i)], new_state + adj[letters[i]][letters[i]]);
		}
	}
	cout << dp[(1 << l) - 1];
}
