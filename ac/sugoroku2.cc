// https://atcoder.jp/contests/abc189/tasks/abc189_f
#include <bits/stdc++.h>
using namespace std;
using pd = pair<double, double>;
const int N = 1e5;
pd suf, dp[N];
int n, m, k;
bool reset[N];
int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int j; cin >> j;
        reset[j] = true;
    }
    for (int i = n - 1; i >= 0; i--) {
        if (reset[i]) dp[i] = {1, 0};
        else dp[i] = {suf.first/m, suf.second/m + 1};
        if (i + m < n) {
            suf.first -= dp[i + m].first; 
            suf.second -= dp[i + m].second;
        }
        suf.first += dp[i].first;
        suf.second += dp[i].second;
    }
    if (abs(1 - dp[0].first) < 1e-9) cout << -1 << endl;
    else cout << fixed << setprecision(3) << dp[0].second / (1 - dp[0].first) << endl;
}
