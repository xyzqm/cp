#include <iostream>
#include <limits.h>
#define int long long
using namespace std;
const int N = 100;
int c[N], m[N], t[N]; // cookies, muffins, total time
int n, tc, tm;
bool works(int x) {
    int nc = max(1ll, tc - x); // spend as many mooneys as possible on cookies
    int nm = tm - (x - (tc - nc)); // spend whatever we didn't spend on cookies
    int lim = min(tc - nc, nm - 1); // how many mooneys we can move from cookies to muffins
    int needed = 0; // how many operations we need 
    // every time we move a mooney from cookies to muffins, time increases by c[i] - m[i]
    for (int i = 0; i < n; i++) {
        int dif = nc * c[i] + nm * m[i] - t[i]; // difference between current time and total time
        int change = c[i] - m[i]; // how much time will change when applying operation
        if (change > 0 && dif <= 0) {
            lim = min(lim, -dif / change);
        }
        else if (dif > 0) {
            if (change >= 0) {
                needed = INT_MAX; // not possible to get dif <= 0
                break;
            }
            needed = max(needed, dif / (-change) + (dif % (-change) != 0));
        }
    }
    return needed <= lim;
}
signed main() {
    int tests; cin >> tests;
    while (tests--) {
        cin >> n >> tc >> tm;
        for (int i = 0; i < n; i++) {
            cin >> c[i] >> m[i] >> t[i];
        }
        int ans = tc + tm - 2;
        for (int dif = tc + tm - 2; dif > 0; dif /= 2) {
            while (ans - dif >= 0 && works(ans - dif)) ans -= dif;
        }
        cout << ans << endl;
    }
}