#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void ac() {
    int n; cin >> n;
    int r = 0;
    while (n) {
        r += 2 * ((n + 1) / 2) * ((n + 1) / 2) - (n + 1) / 2, n /= 2;
    }
    cout << r << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
