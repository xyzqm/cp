// https://codeforces.com/problemset/problem/1203/F2
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int N = 1e2 + 1, R = 6e4 + 1;
int n, r, dp[R];
int main() {
    cin >> n >> r;
    multiset<pii> pos;
    auto cmp = [] (pii a, pii b) {
        return a.second - a.first < b.second - b.first;
    };
    multiset<pii, decltype(cmp)> neg(cmp);
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        if (b >= 0) pos.insert({a, b});
        else neg.insert({a, -b});
    }
    int ans1 = 0;
    for (auto p : pos) {
        if (r < p.first) break;
        r += p.second, ans1++;
    }
    int ans2 = 0;
    for (auto p : neg) {
        for (int i = max(p.first, p.second); i <= r; i++) {
            dp[i - p.second] = max(dp[i - p.second], dp[i] + 1);
        }
    }
    for (int i = 0; i <= r; i++) ans2 = max(ans2, dp[i]);
    cout << ans1 + ans2 << endl;
}