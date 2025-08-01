#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(v) v.begin(), v.end()

const int inf = 1e18;

int n, h0;
vector<array<int, 2>> lr, rl;

// go to start, go the end, then go back
int solve() {
    if (!lr.size()) return inf;
    int mn_l = inf, mx_r = -inf;
    for (auto [l, r] : lr) mx_r = max(mx_r, r), mn_l = min(mn_l, l);
    for (auto [l, r] : rl) {
        mx_r = max(mx_r, r);
        if (r <= h0) mn_l = min(mn_l, l);
    }
    int d = abs(h0 - mn_l) + mx_r - mn_l;
    sort(all(rl));
    // time to sweep
    int best = inf, R = -inf;
    for (auto [l, r] : rl) {
        best = min(best, d + mx_r - l);
        if (r > h0) {
            d += 2 * (r - l) - 2 * max(min(R, r) - l, 0LL);
            R = max(R, r);
        }
    }
    return min(best, d);
}

int32_t main() {
    cin >> n >> h0;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        if (l < r) lr.push_back({l, r});
        else rl.push_back({r, l});
    }
    int x = solve();
    lr.swap(rl);
    for (auto &[l, r] : lr) tie(l, r) = make_pair(-r, -l);
    for (auto &[l, r] : rl) tie(l, r) = make_pair(-r, -l);
    h0 = -h0;
    cout << min(x, solve()) << endl;
}
