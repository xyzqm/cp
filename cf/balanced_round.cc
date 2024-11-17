#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5;
int n, k, a[N];
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a, a + n);
        int ans = 0, cur = 0;
        for (int i = 0; i < n; i++) {
            if (i && a[i] - a[i - 1] > k) ans = max(ans, cur), cur = 1;
            else ++cur;
        }
        ans = max(ans, cur);
        cout << n - ans << endl;
    }
}