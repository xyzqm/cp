#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e3, M = 1e9 + 7;
int n, a[N];
int m_pow(int a, int b) {
	int res = 1;
	while (b) {
		if (b % 2 == 0) a = a * a % M, b /= 2;
		else res = res * a % M, b--;
	}
	return res;
}
signed main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	sort(a, a + n);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			// count number of subsets that meet at (a[i] + a[j]) / 2
			// we can use all numbers < a[i] - (a[j] - a[i]) = 2 * a[i] - a[j]
			int l = lower_bound(a, a + i, 2 * a[i] - a[j]) - a; // # of allowed numbers on left
			// we can use all numbers >= a[j] + a[j] - a[i]
			int r = (a + n) - lower_bound(a + j + 1, a + n, 2 * a[j] - a[i]); // # of allowed numbers on right
			ans = (ans + m_pow(2, l) * m_pow(2, r)) % M;
		}
	}
	cout << ans << endl;
}
