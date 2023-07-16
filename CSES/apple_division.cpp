#include <iostream>
using namespace std;
using ll = long long;
const int N = 20;
int n, p[N];
int main() {
    cin >> n;
    ll S = 0, ans = 1e18;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        S += p[i];
    }
    for (int k = 0; k < (1 << n); k++) {
        ll s = 0;
        for (int i = 0; i < n; i++) if (k & (1 << i)) s += p[i];
        ans = min(ans, abs(S - 2 * s));
    }
    cout << ans << endl;
}