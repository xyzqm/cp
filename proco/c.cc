#include <bits/stdc++.h>
#define int int64_t
using namespace std;


int32_t main() {
    int n, x; cin >> n >> x;
    vector<int> v(n);
    for (int &x : v) cin >> x;
    x = min(n - 1, x);
    int s = 0;
    for (int i = 0; i < x + 1; i++) s += v[i];
    int r = s;
    for (int i = 0; i < n; i++) {
        s -= v[i];
        s += v[(i + x + 1) % n];
        r = max(r, s);
    }
    cout << r << endl;
}
