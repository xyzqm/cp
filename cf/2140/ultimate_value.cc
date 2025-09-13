#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int inf = 1e10;

void ac() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    auto best = array{-inf, -inf};
    int del = 0, sm = 0;
    for (int i = 0, sgn = 1; i < n; i++, sgn *= -1) {
        sm += sgn * a[i];
        best[i & 1] = max(best[i & 1], 2 * -sgn * a[i] - i);
        del = max(del, best[1^(i & 1)] + 2 * -sgn * a[i] + i);
        del = max(del, i - (i & 1));
    }
    cout << del + sm << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
