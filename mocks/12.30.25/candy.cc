#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<array<int, 2>> c(n);
    int min2 = 1e18;
    for (auto &[x, y] : c) {
        cin >> x >> y;
        min2 = min(min2, x + y);
    }
    DBG(min2);
    ranges::sort(c);
    int s = 0, ans = 0;
    for (int i = 0; i <= n; i++) {
        if (s <= m) ans = max(ans, i + (m - s) / min2 * 2);
        if (i < n) s += c[i][0];
    }
    cout << ans << endl;
}
