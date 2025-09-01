#include <bits/stdc++.h>
using namespace std;

int ac() {
    int n; cin >> n;
    vector<int> mn(n, n), mx(n, 0);
    vector<array<int, 2>> v;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        --a;
        mn[a] = min(mn[a], i);
        mx[a] = max(mx[a], i);
    }
    int l = 0, r = n - 1; // valid range [l, r]
    int cl = n, cr = 0; // current range of places that must be conquered
    for (int i = 0; i < n; i++) if (mn[i] < n) {
        cl = min(cl, mn[i]), cr = max(cr, mx[i]);
        // println("{} {} {}", i, cl, cr);
        if (cr - cl > i) return 0;
        l = max(l, cr - i);
        r = min(r, cl + i);
    }
    return max(r - l + 1, 0);
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << ac() << endl;
}
