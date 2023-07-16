#include <iostream>
#include <cmath>
using namespace std;
const int N = 100;
int t, n, k, a[N], d[N];
int main() {
    cin >> t;
    while (t--) {
        cin >> n >> k;
        int s = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (i) d[i] = abs(a[i] - a[i - 1]);
            else d[i] = 0;
            s += d[i];
        }
        // for (int i = 0; i < n; i++) cout << d[i] << " ";
        // cout << endl;
        // cout << s << endl;
        sort(d, d + n, greater<int>());
        // for (int i = 0; i < n; i++) cout << d[i] << " ";
        // cout << endl;
        for (int i = 0; i < k - 1; i++) s -= d[i];
        cout << s << endl;
    }
}