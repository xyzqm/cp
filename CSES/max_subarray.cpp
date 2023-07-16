#include <iostream>
using namespace std;
using ll = long long;
int n;
int main() {
    cin >> n;
    ll mn = 0, p = 0, ans = -1e18;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        p += x;
        ans = max(ans, p - mn);
        mn = min(mn, p);
    }
    cout << ans << endl;
}