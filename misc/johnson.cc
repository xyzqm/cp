#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void ac() {
    int n; cin >> n;
    vector<array<int, 2>> v(n);
    for (auto &[a, b] : v) cin >> a >> b;
    ranges::sort(v, [](array<int, 2> a, array<int, 2> b) {
        int x = min(a[0], b[1]), y = min(b[0], a[1]);
        return x != y ? x < y : a[1] > b[1];
    });
    int cur = 0, sm = 0;
    for (auto &[a, b] : v) sm += a, cur = max(cur, sm) + b;
    cout << cur << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
