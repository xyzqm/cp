#include <iostream>
using namespace std;
#define int long long
const int N = 2e5;
int n, c, a[N];
bool check(int w) {
    int cur = 0;
    for (int i = 0; i < n; i++) {
        cur += (a[i] + 2 * w) * (a[i] + 2 * w);
        if (cur >= c) break;
    }
    return cur >= c;
}
signed main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> c;
        for (int i = 0; i < n; i++) cin >> a[i];
        int l = 0, r = 1e9 + 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }
        cout << l << endl;
    }
}