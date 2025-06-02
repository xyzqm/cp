#include <bits/stdc++.h>
#define int int64_t
using namespace std;

void ac() {
    int n; cin >> n;
    vector<int> v(n);
    for (int &x : v) cin >> x;
    map<int, vector<int>> idx;
    for (int i = 0; i < n; i++) idx[v[i]].push_back(i);
    for (auto &[x, v] : idx) reverse(v.begin(), v.end());
    vector<vector<int>> dp(n, vector<int>());
    set<pair<int, int>> vis;
    int r = 1;
    for (int i = 0; i < n; i++) {
        dp[i].push_back(1);
        for (int x : dp[i]) {
            if (vis.count({i, x})) continue;
            vis.insert({i, x});
            int nx = (x + 1) * v[i] / x;
            while (idx[nx].size() && idx[nx].back() < i) idx[nx].pop_back();
            if (idx[nx].size()) {
                dp[idx[nx].back()].push_back(x + 1);
                r = max(r, x + 1);
            }
        }
    }
    cout << r << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
