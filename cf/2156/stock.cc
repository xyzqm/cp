#include <bits/stdc++.h>
using namespace std;

#define int int64_t

using T = array<int, 3>;

const int inf = 2e9;

int tc = 0;
void ac() {
    int n; cin >> n;
    vector<int> v(n);
    for (int &x : v) cin >> x;
    auto add = [&](T a, int x, int mode) {
        if ((v[a[2]] > v[x]) ^ mode) a[2] = x;
        for (int i : {1, 0}) if ((v[a[i]] > v[a[i + 1]]) ^ mode) swap(a[i], a[i + 1]);
        return a;
    };
    auto rw = [&](const T &x) {
        return max(x[0], x[1]) >= n ? -inf : (v[x[1]] - v[x[0]]) * (x[0] < x[1] ? 1 : -1);
    };
    auto cmp = [&](T a, T b) {
        if (rw(a) != rw(b)) return rw(a) < rw(b);
        else return a < b;
    };
    set<T, decltype(cmp)> ps(cmp);

    // ith smallest/largest index (for sgn = 0/1 respectively)
    vector<vector<int>> opts(n);
    T pre = {n, n, n};
    v.push_back(inf);
    for (int i = 1; i < n; i++) {
        pre = add(pre, i - 1, 0);
        for (int x : pre) opts[i].push_back(x);
    }
    v[n] = -inf;
    T suf = {n, n, n};
    for (int i = n - 1; i --> 0; ) {
        suf = add(suf, i + 1, 1);
        for (int x : suf) opts[i].push_back(x);
    }
    for (int i = 0; i < n; i++) {
        ranges::sort(opts[i], [&](int j, int k) { return rw({i, j}) > rw({i, k}); });
        for (int j = 1; j < 3; j++) for (int k = 0; k < j; k++) {
            ps.insert({i, opts[i][j], opts[i][k]});
        }
    }
    int ans = inf;
    // pick one value in the final tuple to remove
    for (int x : *ps.rbegin()) {
        auto it = ps.rbegin();
        while ((*it)[0] == x || (*it)[1] == x || (*it)[2] == x) ++it;
        ans = min(ans, rw(*it));
    }
    cout << ans << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
