// https://atcoder.jp/contests/arc195/tasks/arc195_d
#include <bits/stdc++.h>
using namespace std;

const int K = 2;
const int N = 2e5 + 1;

int n, a[N], dp[N][K];

int smin(int &a, int b) { return a = min(a, b); }

void ac() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int k = 0; k < K; k++) dp[i][k] = n;
    }
    for (int k = 0; k < K; k++) dp[n - 1][k] = 1;

    for (int i = n - 2; i >= 0; i--) for (int k = 0; k <= min(i, K - 1); k++) {
        // don't swap at all
        smin(dp[i][k], dp[i + 1][0] + (a[i - k] != a[i + 1]));
        // swap i + 1 and i + 2
        if (i + 2 < n) {
            smin(dp[i][k], dp[i + 2][1] + (a[i - k] != a[i + 2]) + (a[i + 1] != a[i + 2]) + 1);
        }
    }
    cout << dp[0][0] << endl;
}

int main() {
    int t; cin >> t;
    while (t--) ac();
}
