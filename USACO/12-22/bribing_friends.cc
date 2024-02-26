// http://www.usaco.org/index.php?page=viewproblem2&cpid=1257
#include <bits/stdc++.h>
using namespace std;
const int N = 2e3;
int n, A, B, P[N], C[N], X[N];
int dp[2 * N + 1];
inline void upd(int& a, int b) {
    a = max(a, b);
}
int main() {
    cin >> n >> A >> B;
    for (int i = 0; i < n; i++) {
        cin >> P[i] >> C[i] >> X[i];
    }
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [](int a, int b) {
        return X[a] < X[b];
    });
    for (int o = 0; o < n; o++) {
        int i = order[o];
        for (int j = 0; j <= A; j++) {
            cout << dp[j] << " ";
            if (j >= C[i]) upd(dp[j - C[i]], dp[j] + P[i]);
        } 
        for (int j = 1; j <= B; j++) {
            cout << dp[j + A] << " ";
            int conv = j / X[i];
            if (conv >= C[i]) upd(dp[A + j - C[i] * X[i]], dp[A + j] + P[i]);
            else if (conv + A >= C[i]) upd(dp[A - (C[i] - conv)], dp[A + j] + P[i]);
        }
        cout << endl;
    }
    int ans = 0;
    for (int i = 0; i <= A + B; i++) {
        cout << dp[i] << " ";
        upd(ans, dp[i]);
    }
    cout << endl;
    cout << ans << endl;
}