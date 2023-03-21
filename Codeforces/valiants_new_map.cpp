#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        int a[n + 1][m + 1], pref[n + 1][m + 1];
        pref[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
                pref[i][0] = pref[0][j] = 0;
            }
        }
        int l = 0;
        for (int dif = 1e6; dif > 0; dif /= 2) {
            while (l + dif <= min(n, m)) {
                int nl = l + dif;
                // cout << nl << endl;
                bool pos = false;
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= m; j++) {
                        pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + (a[i][j] >= nl);
                        if (j >= nl && i >= nl) {
                            pos = pos || (pref[i][j] - pref[i][j - nl] - pref[i - nl][j] + pref[i - nl][j - nl] == nl * nl);
                            // if (pos) break;
                        }
                    }
                    // if (pos) break;
                }
                // for (int i = 1; i <= n; i++) {
                //     for (int j = 1; j <= m; j++) {
                //         cout << pref[i][j] << " ";
                //     }
                //     cout << endl;
                // }
                if (pos) l += dif;
                else break;
            }
        }
        cout << l << endl;
    }
}