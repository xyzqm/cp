#include <bits/stdc++.h>
using namespace std;

void ac() {
    int n; cin >> n;
    auto v = vector(n, array<int, 2>());
    for (auto &[a, b] : v) cin >> a >> b;
    ranges::sort(v, [](array<int, 2> a, array<int, 2> b) {
        if (a[0] > a[1]) swap(a[0], a[1]);
        if (b[0] > b[1]) swap(b[0], b[1]);
        if (a[1] != b[1]) return a[1] < b[1];
        else return a[0] < b[0];
    });
    for (auto [a, b] : v) cout << a << " " << b << " ";
    cout << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
