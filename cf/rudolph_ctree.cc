#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
using ll = long long;
inline ll sq(ll x) { return x * x; }
int main() {
    int t; cin >> t;
    while (t--) {
        int n, d, h;
        cin >> n >> d >> h;
        vector<int> a(n);
        for (int& x : a) cin >> x;
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ans += sq(h);
            if (i && a[i - 1] + h > a[i]) {
                ans -= sq(a[i - 1] + h - a[i]);
            }
        }
        cout << fixed << setprecision(7) << 0.5 * d / h * ans << endl;
    }
}