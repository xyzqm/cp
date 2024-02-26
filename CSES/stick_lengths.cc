#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int n; cin >> n;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;
    sort(a.begin(), a.end());
    ll ans = 0;
    for (ll& x : a) {
        ans += abs(x - a[n / 2]);
    }
    cout << ans << endl;
}