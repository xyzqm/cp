#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int ac() {
    int l, r; cin >> l >> r;
    if (l > r) swap(l, r);
    int ans = 0;
    while (l % 4 != 0 && l <= r) ans ^= l++;
    while (r % 4 != 3 && r >= l) ans ^= r--;
    return ans;
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << ac() << endl;
}
