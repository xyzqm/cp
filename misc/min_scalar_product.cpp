#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int t; cin >> t;
    int c = 0;
    while (t--) {
        c++;
        int n; cin >> n;
        vector<ll> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        sort(a.begin(), a.end());
        sort(b.begin(), b.end(), greater<ll>());
        ll ans = 0;
        for (int i = 0; i < n; i++) ans += a[i] * b[i];
        printf("Case #%d: %lld\n", c, ans);
    }
}