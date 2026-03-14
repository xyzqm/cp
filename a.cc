#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int cnt = 0;
int ac() {
    int n, m; cin >> n >> m;
    vector<array<int, 2>> vs(n);
    int ans = 0;
    multiset<array<int, 2>, greater<>> slopes; // {slope, len}
    // vector<int> tgt;
    for (auto &[b, a] : vs) {
        cin >> a >> b;
        // tgt.push_back(a + b);
        // ans += max(a + b, 0LL);
        slopes.insert({2 * (a + b), 1});
    }
    // sort(tgt.begin(), tgt.end(), greater<>());
    // if (tgt.size() > 1) ans = max(ans, tgt[0] + tgt[1]);
    // else if (m == 1) ans = max(ans, tgt[0]);
    // if (++cnt == 7) {
    //     cout << n << " " << m << "\n";
    //     for (auto &[b, a] : vs) cout << a << " " << b << "\n";
    // }
    // if (!m) return 0;
    // else if (m == 1) return mx_a;
    // DBG(vs);
    sort(vs.begin(), vs.end(), [&](array<int, 2> a, array<int, 2> b) {
       return array{a[0], a[1]} < array{b[0], b[1]};
    });
    DBG(vs);
    auto upd_mx = [&](int cnt, int need) {
        int cur = 0;
        for (auto &[s, len] : slopes)
        if (cnt - len >= 0)
        if (len == 1 || (cnt >= len + need && s > 0)) {
            cur += s * len / 2, cnt -= len;
            DBG(cur);
            need -= (len == 1);
            if (need <= 0) ans = max(ans, cur);
        }
    };
    upd_mx(m, 2 - (m == 1));
    for (auto &[b, a]: vs) {
        slopes.erase(slopes.find({2 * (a + b), 1}));
        slopes.insert({a, 2});
        DBG(slopes);
        upd_mx(m - 1, 2);
        // DBG(ans);
    }
    upd_mx(m, 0);
    return ans;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int s, t; cin >> s >> t;
    while (t--) cout << ac() << "\n";
}
