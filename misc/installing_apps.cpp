// https://open.kattis.com/problems/installingapps
#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 1, C = 1e4 + 1;
int n, c, d[N], s[N], dp[N][C];
pair<int, int> prv[N][C];
void upd(int& a, int b) {
    a = max(a, b);
}
int main() {
    cin >> n >> c;
    for (int i = 0; i < n; i++) cin >> d[i] >> s[i];
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [] (int i, int j) {
        return s[i] - d[i] < s[j] - d[j];
    });
    for (int o = 0; o < n; o++) {
        int i = order[o];
        for (int j = c; j >= 0; j--) {
            upd(dp[o + 1][j], dp[o][j]);
            if (j <= c - max(d[i], s[i])) upd(dp[o + 1][j + s[i]], dp[o][j] + 1);
        }
    }
    int cur = n, res = 0;
    for (int i = 0; i <= c; i++) {
        if (dp[n][i] > dp[n][res]) res = i;
    }
    cout << dp[n][res] << endl;
    vector<int> ans;
    while (res != 0) {
        int i = order[cur - 1];
        if (res >= s[i] && dp[cur - 1][res - s[i]] + 1 == dp[cur][res]) {
            ans.push_back(i);
            res -= s[i];
        }
        cur--;
    }
    for (auto it = ans.rbegin(); it != ans.rend(); it++) {
        cout << *it + 1 << " ";
    }
    cout << endl;
}