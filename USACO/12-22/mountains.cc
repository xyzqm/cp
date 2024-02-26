#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int n; cin >> n;
    vector<int> h(n);
    for (int& x : h) cin >> x;
    vector<set<int>> c(n);
    vector<int> mx(n);
    auto see = [&](int a, int b, int c) {
        return (h[b] - h[a]) * (c - a) <= (h[c] - h[a]) * (b - a);
    };
    for (int i = 0; i < n; i++) {
        int mx = i;
        for (int j = i + 1; j < n; j++) {
            if (see(i, mx, j)) c[i].insert(mx = j);
        }
    }
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        h[--x] += y;
        int mx = x;
        for (int j = x + 1; j < n; j++) {
            if (see(x, mx, j)) c[x].insert(mx = j);
        }
        for (int j = 0; j < x; j++) {
            int mx = *(prev(c[j].upper_bound(x)));
            if (see(j, mx, x)) c[j].insert(mx = x);
            else c[j].erase(x);
            if (mx == x) {
                auto it = c[j].upper_bound(x);
                while (it != c[j].end()) {
                    if (!see(j, x, *it)) {
                        c[j].erase(it);
                        it = c[j].upper_bound(x);
                    } else break;
                }
            }
        }
        int ans = 0;
        for (const auto& s : c) ans += s.size();
        cout << ans << endl;
    }
}