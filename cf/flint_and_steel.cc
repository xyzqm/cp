#include <bits/stdc++.h>
using namespace std;

template <typename F>
struct sgt: vector<int> {
    int n, id;
    F f;
    sgt(int n, int id, F f) : vector(2 * n, id), n(n), id(id), f(f) {}
    void upd(int i, int v) {
        i += n;
        for (at(i) = f(at(i), v); i >>= 1; ) at(i) = f(at(i << 1), at(i << 1 | 1));
    }
    int query(int l, int r) {
        int v = id;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) v = f(v, at(l++));
            if (r & 1) v = f(v, at(--r));
        }
        return v;
    }
};

void ac() {
    int n; cin >> n;
    vector<int> e(n);
    vector<vector<int>> qs(n);
    vector<int> dp(n + 1, n + 1), lst(n + 1);
    auto upd = [&](int u, int v) {
        if (dp[v] + 1 < dp[u]) lst[u] = v, dp[u] = dp[v] + 1;
    };
    for (int i = 0; i < n; i++) {
        cin >> e[i];
        if (e[i]) {
            if (i - e[i] < 0) dp[i] = 1;
            else qs[i - e[i]].push_back(i);
        }
    }
    sgt t(n, n, [&](int i, int j) { return dp[i] < dp[j] ? i : j; });
    int bst = n;
    for (int i = 0; i < n; i++) {
        if (i - e[i] >= 0) upd(i, t.query(i - e[i], i));
        if (i + e[i] >= n) {
            if (dp[i] < dp[bst]) bst = i;
        }
        else if (e[i]) t.upd(i + e[i] - 1, i);
        for (int j : qs[i]) upd(j, t.query(j - e[j], min(j + e[j], n)));
    }
    if (dp[bst] > n) cout << -1 << endl;
    else {
        vector<int> v = {bst};
        while (dp[v.back()] > 1) v.push_back(lst[v.back()]);
        ranges::sort(v, [&](int i, int j) { return e[i] < e[j]; });
        cout << dp[bst] << endl;
        for (int x : v) cout << x + 1 << " ";
        cout << endl;
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
