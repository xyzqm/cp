#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int ac() {
    int n, k; cin >> n >> k;
    vector<array<int, 2>> v(n);
    for (int i = 0; i < n; i++) cin >> v[i][0];
    for (int i = 0; i < n; i++) cin >> v[i][1];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (v[i][0] > v[i][1]) swap(v[i][0], v[i][1]);
        ans += v[i][1] - v[i][0];
    }
    ranges::sort(v);
    int mx_r = -1e16, min_dif = 1e16;
    for (auto [l, r] : v) {
        if (l <= mx_r) return ans;
        else min_dif = min(min_dif, 2 * (l - mx_r));
        mx_r = r;
    }
    return ans + min_dif;
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << ac() << endl;
}
