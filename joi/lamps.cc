#include <bits/stdc++.h>
using namespace std;

void smin(int &a, int b) { a = min(a, b); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    string a, b; cin >> a >> b;
    vector<array<int, 3>> dp(n + 1, {n, n, n});
    auto val = [&](int i, int j) { return j < 2 ? '0' + j : a[i]; };
    auto diff = [&](int i, int j) { return val(i, j) != b[i]; };
    dp[0] = {0, 0, 0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) for (int k = 0; k < 3; k++) {
            smin(dp[i + 1][k], dp[i][j] + (j < 2 && k != j) + (diff(i, j) && (i == n - 1 || !diff(i + 1, k))));
        }
    }
    cout << dp[n][2] << "\n";
}
