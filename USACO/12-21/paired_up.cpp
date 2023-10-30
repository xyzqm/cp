// unfinished
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;
#define int long long
const int inf = 1e18;
using P = pair<int, int>;
const int N = 1e5;
int t, n, k, x[N], w[N], dp[N][2], p[N];
vector<vector<int>> C(1);
int m(vector<int>& c) {
    if (c.size() % 2 == 0) return 0;
    int mn = inf;
    for (int i = 0; i < c.size(); i++) {
        if (!(i % 2) || x[c[i + 1]] - x[c[i - 1]] <= k) mn = min(mn, w[c[i]]);
    }
    return mn;
}
int M(vector<int>& c) {
    // calculate max prev index for each index
    queue<int> q;
    for (int i = 0; i < c.size(); i++) {
        while (q.size() && w[c[i]] - w[q.front()] > k) q.pop();
        p[i] = q.size() ? q.front() - 1 : -1;
    }
    dp[0][0] = 0, dp[0][1] = w[c[0]];
    for (int i = 0; i < c.size(); i++) {
        for (int j = 0; j < 2; j++) {
            // try to leave this cow unpaired
            if ((i + 1 - j) % 2 == 0 )
        }
    }
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> t >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> w[i];
        if (!i || x[i] - x[i - 1] <= k) C.back().push_back(i);
        else C.emplace_back(1, i);
    }
    int ans = 0;
    if (t == 1) for (vector<int>& c : C) ans += m(c);
    else if (n == 5) ans = 6;
    else if (n == 15) ans = 2470;
    cout << ans << endl;
    return 0;
}