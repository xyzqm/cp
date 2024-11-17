#include <bits/stdc++.h>
using namespace std;
#define int long long

void ac() {
    int b, n; cin >> b >> n;
    vector<int> s(n);
    for (int &x : s) cin >> x;
    auto ck = [&](int h) {
        int d = 0;
        for (int x : s) {
            d += max(x - h, 0LL);
        }
        return d;
    };
    auto danger = [&](int h) {
        int d = 0;
        for (int x : s) {
            d += max(h - x, 0LL);
        }
        return d;
    };
    int x = 0, r = *max_element(s.begin(), s.end());
    for (int d = r; d > 0; d >>= 1) {
        while (x + d <= r && ck(x + d) >= b) x += d;
    }
    if (ck(x) > b) ++x;
    int y = x;
    for (int d = r; d > 0; d >>= 1) {
        while (y + d <= r && danger(y + d) == danger(x)) y += d;
    }
    cout << y << endl;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
