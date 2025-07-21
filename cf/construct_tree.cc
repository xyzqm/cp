#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<T> vec(int n, T v = 0) { return vector(n, v); }
template <typename T, typename ...Args>
auto vec(int n, Args... args) { return vector(n, vec(args...)); }

void smin(int &a, int b) { a = min(a, b); }

int ac() {
    int n, d; cin >> n >> d;
    auto l = vec(n, 0);
    for (int &x : l) cin >> x;
    sort(l.begin(), l.end());
    if (l.back() + l[l.size() - 2] > d) return 0;
    auto dp = vec(d + 1, bitset<2001>());
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        if (i == n - 1) for (int j = 0; j <= d - l[i]; j++) if (dp[j][d - l[i] - j]) return 1;
        for (int j = d; j >= 0; j--) {
            if (j + l[i] <= d) dp[j + l[i]] |= dp[j];
            dp[j] |= dp[j] << l[i];
        }
    }
    for (int i = 0; i <= d; i++) if (dp[i][d - i] && min(i, d - i) >= l.back()) return 1;
    return 0;
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << vector{"NO", "YES"}[ac()] << endl;
}
