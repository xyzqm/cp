#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 1e9 + 7;
const int K = 20;

struct dat { int sm, cnt; } dp[K + 1][1 << K];

void ad(int &x, int y) { x = (x + y) % M; }

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, K; cin >> n >> K;
    vector<int> v(n);
    for (int &x : v) {
        cin >> x;
        ++dp[0][x].cnt;
    }
    for (int k = 0; k < K; k++) {
        for (int j = k + 1; j --> 0; ) {
            for (int i = 0; i < (1 << K); i++) {
                ad(dp[j + 1][i ^ (1 << k)].sm, dp[j][i].sm);
                ad(dp[j + 1][i ^ (1 << k)].cnt, dp[j][i].cnt);
                if (i >> k & 1) {
                    ad(dp[j + 1][i].sm, dp[j][i].sm + dp[j][i].cnt);
                    ad(dp[j + 1][i].cnt, dp[j][i].cnt);
                    dp[j][i] = {0, 0};
                }
            }
        }
    }
    vector<int> invs{0, 1};
    for (int i = 2; i <= K; ++i)  // mod inverses in O(K) time
        invs.push_back((M / i + 1) * invs[i - M % i] % M);

    for (int x : v) {
        int r = 0;
        for (int k = 1; k <= K; k++) {
            ad(r, dp[k][x].sm * invs[k]);
        }
        cout << r << "\n";
    }
}
