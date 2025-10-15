#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 1e9 + 7;

struct mint {
    int v = 0;
    mint() {}
    mint(int v) : v(v) {}
    mint operator*(mint o) { return v * o.v % M; }
    mint operator+(mint o) { return (v + o.v) % M; }
    void operator+=(mint o) { v = (v + o.v) % M; }
    mint operator-(mint o) { if (int x = v - o.v; x < 0) return x + M; else return x; }
    mint inv() {
        mint x = v, r = 1;
        for (int p = (M - 2) * 2; p >>= 1; x = x * x) if (p & 1) r = r * x;
        return r;
    }
};

mint ac() {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int &x : a) cin >> x;
    int tot = n + 1;
    for (int i = 0; i <= n; i++)
        if (a[i] > n) return 0;
        else if (a[i] > 0 && a[a[i]] == -1) a[a[i]] = i;
    for (int i = 0; i <= n; i++) if (a[i] >= 0) {
        if (a[i] > 0 && a[a[i]] != i) return 0;
        else --tot;
    }
    assert(a[0] == -1);
    --tot;
    vector<mint> dp(tot + 1);
    dp[0] = 1;
    for (int i = 1; i <= tot; i++) dp[i] = dp[i - 1] + dp[i - 1] * (i < tot || a[n] != -1) + (i > 1 ? dp[i - 2] * (i - 1) : 0);
    return dp[tot];
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) cout << ac().v << endl;
}
