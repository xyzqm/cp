#include <bits/stdc++.h>
using namespace std;

#define int int64_t

array<int, 2> operator+(array<int, 2> a, array<int, 2> b) {
    if (b[1] > a[1]) return {max(a[1], b[0]), b[1]};
    else return {max(a[0], b[1]), a[1]};
};

int32_t main() {
    int n; cin >> n;
    vector<int> a(1 << n);
    for (int &x : a) cin >> x;
    vector<array<int, 2>> dat(1 << n);
    for (int i = 0; i < (1 << n); i++) dat[i] = {0, a[i]};
    for (int k = 0; k < n; k++) for (int i = 0; i < (1 << n); i++) if (i >> k & 1) {
        dat[i] = dat[i] + dat[i ^ (1 << k)];
    }
    int ans = 0;
    for (int i = 1; i < (1 << n); i++) {
        cout << (ans = max(ans, dat[i][0] + dat[i][1])) << "\n";
    }
}
