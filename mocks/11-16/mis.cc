#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#include "mint.h"
using namespace std;

const int N = 21;
const int M = 998244353;
int n, m, g[N], mis[1 << N];
ll dp[1 << N][N];
ll ad(ll &u, ll v) { return u = (u + v) % M; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u] |= (1 << v);
        g[v] |= (1 << u);
    }
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) if (!(i >> j & 1)) {
            mis[i | (1 << j)] = max(mis[i | (1 << j)], mis[i] + !(g[j] & i));
        }
    }
    dp[(1 << n) - 1][0] = 1;
    for (int i = (1 << n); i --> 0; ) {
        for (int j = n; j >= 0; j--) if (dp[i][j]) {
            if (j) ad(dp[i][j - 1], dp[i][j] * j);
            for (int k = 0; k < n; k++) if (i >> k & 1) {
                int w = i ^ (i & g[k]) ^ (1 << k);
                if (mis[i] > mis[w] + 1) continue;
                ad(dp[w][j + __builtin_popcount(i & g[k])], dp[i][j]);
            }
        }
    }
    mint f = 1;
    for (int i = 1; i <= n; i++) f = f * i;
    cout << mint{dp[0][0]} / f << endl;
}
