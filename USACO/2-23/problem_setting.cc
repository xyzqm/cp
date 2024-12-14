#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 1;
const int M = 1e9 + 7;
const int K = 10;

struct mint {
	int v;
	mint() : v(0) {}
	mint(int v) : v(v % M) {}
	operator int() { return v; }
	int operator+=(int x) { return v = mint(v + x); }
};
int v[N], c[1 << 20];
mint w[N], dp[1 << K][1 << K];

signed main() {
	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++) {
		string s; cin >> s;
		for (int j = 0; j < n; j++) if (s[j] == 'H') v[j] |= (1 << i);
	}
	for (int i = 0; i < n; i++) ++c[v[i]];
	w[1] = 1;
	for (int i = 2; i <= n; i++) w[i] = i * (w[i - 1] + 1);
	mint r = w[c[0]] + 1;
	for (int i = 0; i < (1 << K); i++) dp[0][i] = r;
	for (int i = 1; i < (1 << (2 * K)); i++) {
		mint x = 0;
		for (int j = i >> K; ; j = (j - 1) & (i >> K)) {
			x += dp[j][i & 1023];
			if (!j) break;
		}
		r += (x = x * w[c[i]]);
		for (int j = 1023 - (i & 1023); ; j = (j - 1) & (1023 - (i & 1023))) {
			dp[i >> K][1023 - j] += x;
			if (!j) break;
		}
	}
	cout << r - 1 << endl;
}
