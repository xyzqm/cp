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
    int n, q; cin >> n >> q;
    vector<int> mx(n);
    while (q--) {
        int t, l, r, v; cin >> t >> l >> r >> v;
        assert(t == 2);
        for (int i = --l; i < r; i++) mx[i] = v;
    }
    int ans = 0, cur = 0;
    multiset<int> opts;
    sort(mx.begin(), mx.end());
    for (int v : mx) {
        while (cur < v) opts.insert(0), cur++;
        if (!opts.size()) {
            cout << -1 << endl;
            return 0;
        }
        int cost = *opts.begin();
        ans += 2 * cost + 1;
        opts.erase(opts.begin());
        opts.insert(cost + 1);
    }
    cout << ans << endl;
}
