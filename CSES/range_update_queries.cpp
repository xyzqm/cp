#include <iostream>
using namespace std;
using ll = long long;
const int N = 2e5;
const int B = 500;
int n, q;
ll a[N], s[N / B + 1];
int main() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            ll u;
            cin >> l >> r >> u;
            --l, --r;
            int L = l / B, R = r / B;
            if (L == R) for (int i = l; i <= r; i++) a[i] += u;
            else {
                for (int i = l; i < (L + 1) * B; i++) a[i] += u;
                for (int i = L + 1; i < R; i++) s[i] += u;
                for (int i = R * B; i <= r; i++) a[i] += u;
            }
        } else {
            int k;
            cin >> k;
            --k;
            cout << a[k] + s[k / B] << endl;
        }
    }
}