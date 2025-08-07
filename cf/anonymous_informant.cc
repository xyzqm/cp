#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int ac() {
    int n, k; cin >> n >> k;
    vector<int> a(n), vis(n);
    for (int &x : a) cin >> x;
    int lst = n - 1;
    while (k) {
        if (vis[lst]) return 1;
        vis[lst] = true;
        if (a[lst] > n) return 0;
        else lst -= a[lst];
        if (lst < 0) lst += n;
        k--;
    }
    return 1;
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << vector{"No", "Yes"}[ac()] << endl;
}
