#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 998244353;
void ad(int &a, const int b) { if ((a += b) >= M) a -= M; }
void sb(int &a, const int b) { if ((a -= b) < 0) a += M; }
int inv(int x) {
    int iv = 1;
    for (int pw = M - 2; pw; x = x * x % M, pw >>= 1) if (pw & 1) iv = iv * x % M;
    return iv;
}

const int B = 700;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k, l, r; cin >> n >> k >> l >> r;

    // first process items with weight < B
    auto dp = array{vector<int>(n + 1), vector<int>(n + 1)};
    dp[1][0] = 1;
    for (int i = l; i < min(r + 1, B); i++) for (int j = i; j <= n; j++) ad(dp[1][j], dp[1][j - i]);
    auto ws = dp[1]; // ws[i] = # of ways to make a sum of i

    // process items with weight >= B
    if (r >= B) {
        int lb = max(l, B);
        for (int i = 1; i <= n / lb; i++) { // i = # of items with weight >= B
            dp[0].swap(dp[1]);
            dp[1].assign(n + 1, 0);
            for (int j = lb * i; j <= n; j++) {
                ad(dp[1][j], dp[1][j - i]); // increment all items by 1
                ad(dp[1][j], dp[0][j - lb]); // add item with weight lb
                if (j >= r + i) sb(dp[1][j], dp[0][j - r - i]);
                ad(ws[j], dp[1][j]);
            }
        }
    }

    int sm = 0;
    for (int i = l; i <= r; i++) { // enumerate the marked value which appears >= k times
        if (n - k * i >= 0) ad(sm, ws[n - k * i]);
    }
    cout << (sm * inv(ws[n]) % M) << endl;
}
