#include <bits/stdc++.h>
using namespace std;

void ac() {
    int n, k; cin >> n >> k;
    int tgt = n * (n - 1) / 2 - k;
    auto dp = vector(n + 1, vector(n * (n - 1) / 2 + 1, 0));
    auto lst = dp;
    dp[0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int v = 0; v <= i * (i - 1) / 2; v++) if (dp[i][v]) {
        for (int j = 1; i + j <= n; j++) {
            dp[i + j][v + j * (j - 1) / 2] = 1;
            lst[i + j][v + j * (j - 1) / 2] = j;
        }
    }
    if (!dp[n][tgt]) cout << 0 << endl;
    else {
        for (int cur = n; cur > 0; ) {
            int x = lst[cur][tgt];
            for (int i = cur - x + 1; i <= cur; i++) cout << i << " ";
            tgt -= x * (x - 1) / 2;
            cur -= x;
        }
        cout << endl;
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
