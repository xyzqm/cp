#include <bits/stdc++.h>
using namespace std;
const int N = 1e6;
int n, dp[N + 1];
int main() {
    cin >> n;
    fill(dp, dp + n + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int c = i;
        while (c) {
            int d = c % 10;
            c /= 10;
            if (!d) continue;
            dp[i] = min(dp[i], dp[i - d] + 1);
        }
    }
    cout << dp[n];
}