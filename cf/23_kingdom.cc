#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int ac() {
    int n; cin >> n;
    vector<int> v(n);
    for (int &x : v) cin >> x;
    auto comp = [&](int s, int e, int step) {
        set<int> rem;
        for (int i = 0; i < n; i++) rem.insert(i);
        vector<array<int, 2>> res;
        res.push_back({s - step, 0});
        for (int i = s; i != e; i += step) {
            auto it = rem.upper_bound(v[i] - 1);
            if (it != rem.begin()) {
                rem.erase(prev(it));
                res.push_back({i, res.back()[1] + i});
            }
        }
        return res;
    };
    auto pre = comp(0, n, 1);
    auto suf = comp(n - 1, -1, -1);
    for (int i = min(pre.size(), suf.size()); i --> 0; ) if (pre[i][0] < suf[i][0]) return suf[i][1] - pre[i][1];
    assert(false);
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << ac() << endl;
}
