#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int inf = 1e15;

int ac() {
    int n; cin >> n;
    vector<int> a(n), b(n), pre(n);
    for (int &x : a) cin >> x;
    partial_sum(a.begin(), a.end(), pre.begin());
    for (int &x : b) { cin >> x; --x; }
    int ans = 0;
    map<int, int> opt;
    opt[-1] = opt[0] = 0, opt[n] = inf;
    for (int i = 0; opt.size() && i < n; i++) {
        auto it = opt.lower_bound(i);
        int cost = it->second;
        ans = max(ans, pre[i] - cost);
        if (opt.lower_bound(b[i]) -> second <= cost + a[i]) continue;
        while (opt.size()) {
            auto it = --opt.lower_bound(b[i]);
            if (cost + a[i] < it->second) opt.erase(it);
            else break;
        }
        opt[b[i]] = cost + a[i];
    }
    return ans;
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << ac() << endl;
}
