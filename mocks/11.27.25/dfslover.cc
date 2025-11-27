#include <bits/stdc++.h>
using namespace std;

const int M = 998244353;

#define int int64_t

int inv(int x) { return x <= 1 ? x : M - M / x * inv(M % x) % M; }


int32_t main() {
    int n; cin >> n;

    // precompute factorials and inverses
    vector<int> fac(n + 1), iv(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % M;
    for (int i = 1; i <= n; i++) iv[i] = inv(i);

    vector<int> a(n);
    for (int &x : a) cin >> x;
    sort(a.begin(), a.end());
    a.insert(a.begin(), 0);
    vector<int> dp(n + 2);
    dp[0] = M - 1;
    for (int i = 1; i <= n + 1; i++) {
        vector<int> oc(1e4);
        int d = 1;
        for (int j = i - 1; j >= 0; j--) {
            dp[i] += M - (dp[j] * fac[i - j - 1] % M * d % M);
            d *= iv[++oc[a[j]]];
            dp[i] %= M, d %= M;
        }
    }
    cout << dp[n + 1] << endl;
}
