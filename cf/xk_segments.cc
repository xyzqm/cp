#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
    int n, x, k; cin >> n >> x >> k;
    map<int, int> c;
    for (int i = 0; i < n; i++) { int x; cin >> x; ++c[x]; }
    map<int, int> mp;
    int t = 0;
    for (auto [a, c] : c) {
        mp[(a - 1) / x] += c;
        t += mp[a / x - k] * c;
    }
    cout << t << endl;
}
