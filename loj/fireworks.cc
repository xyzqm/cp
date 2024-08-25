#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 1;
// q[i] stores the points at which hull slope increases by 1
__gnu_pbds::priority_queue<int> q[N];
int p[N], w[N], s[N];

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	for (int i = 2; i <= n + m; i++) cin >> p[i] >> w[i];
	int S = w[1];
	auto t = [&](int i) {
	    int x = q[i].top();
	    return q[i].pop(), x;
	};
	for (int i = n + m; i > 1; i--) {
		if (i > n) q[i].push(0), q[i].push(0);
		// search for section with slope 0
		// max slope = # of children, since each child has max slope 1
		for (int j = 0; j < s[i] - 1; j++) q[i].pop();
		int r = t(i);
		int l = t(i);
		q[i].push(l + w[i]);
		q[i].push(r + w[i]);
		q[p[i]].join(q[i]);
		++s[p[i]], S += w[i];
	}
	// f(0) = S, now we just need to find min value
	// first pop out positive slope section
	while (s[1]--) q[1].pop();
	// now just subtract until we reach desired answer
	while (q[1].size()) S -= t(1);
	cout << S << endl;
}

