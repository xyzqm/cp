#include <iostream>
using namespace std;
using ll = long long;
const int N = 2e5;
const int B = 500;
ll a[N], s[N / B + 1];
int n, q;
int main() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s[i / B] += a[i];
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        int L = l / B, R = r / B;
        ll ans = 0;
        if (L == R) for (int i = l; i <= r; ++i) ans += a[i];
        else {
            for (int i = l; i < (L + 1) * B; ++i) ans += a[i];
            for (int i = L + 1; i < R; ++i) ans += s[i];
            for (int i = R * B; i <= r; ++i) ans += a[i];
        }
        cout << ans << endl;
    }
}