#include <bits/stdc++.h>
#define int int64_t
using namespace std;

void ac() {
    int n, k; cin >> n >> k;
    vector<int> p(n + 1), t(n + 1), s(n + 1);
    vector<deque<int>> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        pos[p[i]].push_back(i);
        cin >> t[i];
    }
    partial_sum(t.begin(), t.end(), s.begin());
    vector<int> dp(n + 1);
    for (int i = 1; i <= n; i++) dp[i] = -s[i - 1];
    // we either stay until next occurence of this position or move immediately after this one ends
    int prv = 0, mx = 0;
    for (int i = 1; i <= n; i++) {
        while (prv < n && s[prv + 1] + k <= s[i - 1]) mx = max(mx, dp[++prv]);
        if (s[prv] + k <= s[i - 1]) {
            dp[i] = max(dp[i], mx - s[i - 1]);
        }
        dp[i] += s[i];
        // jump immediately
        auto it = upper_bound(s.begin(), s.end(), s[i] + k);
        if (it != s.end()) {
            dp[it - s.begin()] = max(dp[it - s.begin()], dp[i] - (s[i] + k));
        }
        // wait
        assert(pos[p[i]].front() == i);
        pos[p[i]].pop_front();
        if (pos[p[i]].size()) {
            int nx = pos[p[i]].front();
            dp[nx] = max(dp[nx], dp[i] - s[nx - 1]);
        }

    }
    cout << *max_element(dp.begin(), dp.end()) << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
