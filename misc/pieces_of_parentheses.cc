// https://tinyurl.com/parenthesesproblem

#include <bits/stdc++.h>
using namespace std;
const int N = 301;
int n, l[N], r[N], len[N], dp[N][N * N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        len[i] = s.length();
        for (char c : s) {
            if (c == '(') l[i]++;
            else if (l[i]) l[i]--;
            else r[i]++;
        }
    }
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [](int i, int j) {
        if (l[i] - r[i] > 0) {
            if (l[j] - r[j] < 0) return true;
            else return r[i] < r[j];
        } else {
            if (l[j] - r[j] > 0) return false;
            else return l[i] > l[j];
        }
    });
    fill(&dp[0][0], &dp[0][0] + N * N * N, INT_MIN);
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        int x = order[i];
        for (int j = 0; j < N * N; j++) {
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            if (dp[i][j] == INT_MIN || r[x] > j || j + l[x] - r[x] >= N * N) continue;
            dp[i + 1][j + l[x] - r[x]] = max(dp[i + 1][j + l[x] - r[x]], dp[i][j] + len[x]);
        }
    }
    cout << dp[n][0];
}