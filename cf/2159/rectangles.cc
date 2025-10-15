#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void ac() {
    int n, m; cin >> n >> m;
    auto a = vector(min(n, m), vector(max(n, m), n * m + 1));
    auto ans = a;
    auto dp = vector(min(n, m), vector(max(n, m), array{0LL, n * m + 1}));
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        char c; cin >> c;
        (n < m ? a[i][j] : a[j][i]) = (c == '1');
    }
    for (int i = 0; i < min(n, m); i++) for (int j = i + 1; j < min(n, m); j++) {
        vector<int> lf(max(n, m), -2 * n * m);
        for (int k = 0; k < max(n, m); k++) {
            if (a[i][k] && a[j][k]) lf[k] = k;
            if (k + 1 < max(n, m)) lf[k + 1] = lf[k];
        }
        for (int rt = 2 * n * m, k = max(n, m); k --> 0; ) {
            int w = rt - lf[k];
            if (a[i][k] && a[j][k]) {
                rt = k;
                if (k) w = min(w, rt - lf[k - 1]);
            }
            auto &[idx, val] = dp[j][k];
            if (int area = (w + 1) * (j - i + 1); area < val) {
                assert(idx <= i);
                for (; idx < i; idx++) ans[idx][k] = min(ans[idx][k], val);
                val = area;
            }
        }
    }
    for (int i = 0; i < min(n, m); i++)
        for (int j = 0; j < max(n, m); j++)
            for (auto [idx, val] = dp[i][j]; idx <= i; idx++)
                ans[idx][j] = min(ans[idx][j], val);
    auto eval = [&](int x) { return x <= n * m ? x : 0; };
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        cout << eval(n < m ? ans[i][j] : ans[j][i]) << " \n"[j == m - 1];
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
