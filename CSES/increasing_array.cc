#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    int ans = 0;
    for (int i = 1; i < n; i++) {
        ans += max(0LL, a[i - 1] - a[i]);
        a[i] = max(a[i], a[i - 1]);
    }
    cout << ans << endl;
}