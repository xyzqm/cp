#include <iostream>
#include <cmath>
using namespace std;
using ll = __int128;
ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b % 2) --b, res *= a;
        else a *= a, b /= 2;
    }
    return res;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        ll x;
        long long y; cin >> y;
        x = y;
        bool works = false;
        for (int n = 3; n < 60; n++) {
            ll k = 2;
            ll mx = ceil(pow(x, 1.0 / (n - 1)));
            // cout << mx << endl;
            for (ll dif = 1e9; dif > 0; dif /= 2) {
                while (k + dif <= mx && (pw(k + dif, n) - 1) / (k + dif - 1) <= x) k += dif;
            }
            // cout << (int) k << " " << n << endl;
            if (k <= mx && (pw(k, n) - 1) / (k - 1) == x) {
                works = true;
                break;
            }
        }
        cout << (works ? "YES" : "NO") << endl;
    }
}