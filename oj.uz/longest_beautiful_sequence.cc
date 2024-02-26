#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int N = 1e5;
const int B = 10;
int bc[1 << B][1 << B];  // bc[i][j] = bit_count(i & j)
struct state {
	int length = 0, end = 0;
    state() {}
	state(int l, int e) : length(l), end(e) {}
};
state dp[1 << B][1 << B][B + 1];

int main() {
	// preprocess:
	for (int i = 0; i < (1 << B); i++) {
		for (int j = 0; j < (1 << B); j++) {
			bc[i][j] = __builtin_popcount(i & j);
		}
	}

	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	vector<int> k(n);
	for (int i = 0; i < n; i++) cin >> k[i];
	int ans = 1, best_i = 0;  // best_i: best index to end subsequence at
	vector<int> prv(n);       // prv[i]: best index to include before i
	iota(prv.begin(), prv.end(), 0);  // prv[i] = i

	for (int i = 0; i < n; i++) {
		int l = a[i] >> 10, r = a[i] % (1 << 10);  // l(a[i]), r(a[i])
		int lbs = 1;  // length of longest lbs that ends at i

		// enumerate all possibilities for l(prev_num)
		for (int j = 0; j < (1 << B); j++) {
			// here, we use the fact that
			// bc[x][y] = bc[l(x)][l(y)] + bc[r(x)][r(y)],
			// or bc[r(x)][r(y)] = bc[x][y] - bc[l(x)][l(y)]

			// required value of bc[r(x)][r(y)]
			int needed = k[i] - bc[j][l];
			if (needed < 0 || needed > 10) continue;
			if (dp[j][r][needed].length + 1 > lbs) {
				lbs = dp[j][r][needed].length + 1;
				prv[i] = dp[j][r][needed].end;
			}
		}

		if (lbs > ans) {
			ans = lbs;
			best_i = i;
		}

		// update all answers a[i] affects
		for (int j = 0; j < (1 << B); j++) {
			state &new_state = dp[l][j][bc[r][j]];
			if (lbs > new_state.length) {
				new_state.length = lbs;
				new_state.end = i;
			}
		}
	}
	cout << ans << endl;
	vector<int> res;
	while (prv[best_i] != best_i) {
		res.push_back(best_i);
		best_i = prv[best_i];
	}
	res.push_back(best_i);
	reverse(res.begin(), res.end());
	for (int x : res) cout << x + 1 << " ";
}