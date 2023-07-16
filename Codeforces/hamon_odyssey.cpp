#include <iostream>
using namespace std;
const int N = 2e5;
int n, a[N];
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        int s = INT_MAX;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            s &= a[i];
        }
        if (s) cout << 1 << endl;
        else {
            int ans = 0;
            s = INT_MAX;
            for (int i = 0; i < n; i++) {
                s &= a[i];
                if (s == 0) ++ans, s = INT_MAX;
            }
            cout << ans << endl;
        }
    }
}