#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void ac() {
    int n; cin >> n;
    map<int, vector<int>> pos;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    using info = array<array<array<int, 2>, 2>, 2>; // int[2][2][2]
    auto get_mx = [](const info &i, int j) {
        int ans = 0;
        for (int a : {0, 1}) for (int b : {0, 1}) ans = max(ans, i[a][b][j]);
        return ans;
    };
    vector<info> dp(n);
    for (int i = 0; auto &info : dp) info[1][1] = {1, 1 + a[i++]};
    // DSU
    auto fa = ranges::to<vector>(ranges::iota_view{0, n});
    auto rt = [&](this auto rt, int x) -> int { return fa[x] = (x == fa[x] ? x : rt(fa[x])); };

    int mx_sz = 0;
    multiset<int> difs;
    vector<bool> active(n);
    auto unite = [&](int x, int y) {
        if (!active[x] || !active[y]) return false;
        x = rt(x), y = rt(y);
        if (x == y) return false;
        if (x > y) swap(x, y);
        for (int t : {x, y}) {
            mx_sz -= get_mx(dp[t], 0);
            difs.erase(difs.find(get_mx(dp[t], 1) - get_mx(dp[t], 0)));
        }
        fa[y] = x;
        info tmp{}, &l = dp[x], &r = dp[y];
        for (int i : {0, 1}) for (int j : {0, 1})
        for (int k : {0, 1}) for (int h : {0, 1})
        for (int a : {0, 1}) for (int b : {0, 1}) if (!(j && k) && !(a && b)) {
            tmp[i][h][a + b] = max(tmp[i][h][a + b], l[i][j][a] + r[k][h][b]);
        }
        mx_sz += get_mx(tmp, 0);
        difs.insert(get_mx(tmp, 1) - get_mx(tmp, 0));
        dp[x] = tmp;
        return true;
    };
    auto activate = [&](int i) {
        active[i] = true;
        mx_sz += get_mx(dp[i], 0);
        difs.insert(get_mx(dp[i], 1) - get_mx(dp[i], 0));
        // println("{} {} {} {}", i, mx_sz, difs, dp[i]);
        if (i) unite(i - 1, i);
        if (i + 1 < n) unite(i, i + 1);
    };
    int ans = 0;
    for (auto it = pos.rbegin(); it != pos.rend(); ++it) {
        for (int x : it->second) activate(x);
        ans = max(ans, it->first + mx_sz + *(--difs.end()));
        // println("{} {}", mx_sz, difs);
    }
    cout << ans << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
