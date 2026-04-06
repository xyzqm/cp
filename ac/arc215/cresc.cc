#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

using mint = modint1000000007;

mint choose(int n, int m) {
    mint num = 1;
    for (int i = n; i > n - m; i--) num *= i;
    mint denom = 1;
    for (int i = 1; i <= m; i++) denom *= i;
    return num * denom.inv();
}

mint stars(int m, int n) { return choose(m + n, n); }

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    ++n;
    int e = n >> 1, o = n - (n >> 1);
    mint res = 0;
    if (e) res += stars(m, e - 1) * stars(m, o);
    if (o) res += stars(m, e) * stars(m, o - 1);
    if (e && o) res -= stars(m, e - 1) * stars(m, o - 1);
    cout << res.val() << "\n";
}
