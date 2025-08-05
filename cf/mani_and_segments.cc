// https://codeforces.com/contest/2101/problem/D
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int ac() {
    int n; cin >> n;
    vector<int> v(n), idx(n + 1);
    for (int i = 0; int &x : v) {
        cin >> x;
        idx[x] = ++i;
    }
    auto solve = [&](int s, int e, int step) {
        set<int> dec = {0}, all;
        vector<int> res(n + 1), prv(n + 1);
        for (int v = s; v != e + step; v += step) {
            auto it = dec.lower_bound(idx[v]);
            res[v] = idx[v] - prv[*prev(it)];
            it = all.lower_bound(idx[v]);
            if (it != all.end()) {
                if (!prv[*it]) dec.insert(*it);
                prv[*it] = idx[v];
            }
            all.insert(idx[v]);
        }
        return res;
    };
    auto less_l = solve(1, n, 1);
    auto more_l = solve(n, 1, -1);
    ranges::for_each(idx, [&](int &x) { x = n + 1 - x; });
    auto less_r = solve(1, n, 1);
    auto more_r = solve(n, 1, -1);
    ranges::for_each(idx, [&](int &x) { x = n + 1 - x; });
    vector<array<int, 2>> intervals;
    for (auto [i, a, b, c, d] : views::zip(idx, less_l, more_l, less_r, more_r)) intervals.push_back({i - min(a, b) + 1, i + min(c, d) - 1});
    ranges::sort(intervals);
    auto c2 = [](int l, int r) { return l <= r ? (r - l + 2) * (r - l + 1) / 2 : 0; };
    int ans = 0;
    for (int mx_r = 0; auto &[l, r] : intervals) {
        ans += c2(l, r) - c2(l, min(r, mx_r));
        mx_r = max(mx_r, r);
    }
    return ans;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) cout << ac() << endl;
}
