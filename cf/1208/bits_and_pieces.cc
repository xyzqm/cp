#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int K = 21;

array<int, 2> operator+(array<int, 2> a, array<int, 2> b) {
    if (b[1] > a[1]) swap(a, b);
    return {max(a[0], b[1]), a[1]};
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    auto dp = vector(1 << K, array<int, 2>{-1, -1});
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[a[i]] = dp[a[i]] + array{-1LL, i};
    }
    for (int k = 0; k < K; k++) for (int i = 0; i < 1 << K; i++) if (!(i >> k & 1)) {
        dp[i] = dp[i] + dp[i ^ (1 << k)];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int cur = a[i];
        for (int k = K; k --> 0; ) if (dp[(cur | (1 << k)) ^ a[i]][0] > i) cur |= 1 << k;
        if (dp[cur ^ a[i]][0] > i) ans = max(ans, cur);
    }
    cout << ans << endl;
}
