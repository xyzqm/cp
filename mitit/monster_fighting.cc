#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int ac() {
    int n; cin >> n;
    vector<pair<int, int>> a;
    multiset<int> b[2];
    for (int i = 0; i < n; i++) {
        int x, t; cin >> x >> t;
        a.push_back({x, t});
    }
    for (int i = 0; i < n; i++) {
        int x, t; cin >> x >> t;
        b[t].insert(x);
    }
    sort(a.begin(), a.end());
    for (auto [x, t] : a) {
        auto it = b[t].upper_bound(2 * x);
        if (it != b[t].begin()) b[t].erase(prev(it));
        else {
            it = b[t ^ 1].upper_bound(x);
            if (it == b[t ^ 1].begin()) return 0;
            else b[t ^ 1].erase(prev(it));
        }
    }
    return 1;
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << (ac() ? "YES\n" : "NO\n");
}
