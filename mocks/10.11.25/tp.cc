#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int32_t main() {
    int p, t; cin >> p >> t;
    // assert(p > 2);
    auto pw = [&](int x, int e) {
        int r = 1;
        for ( ; e; x = x * x % p, e >>= 1) if (e & 1) r = r * x % p;
        return r;
    };
    auto sub = [&](int a, int b) { return (a - b + p) % p; };
    auto sum = [&](int a, int b) { return (a + b) % p; };
    int inv2 = pw(2, p - 2);
    while (t--) {
        int x0, y0, x1, y1; cin >> x0 >> y0 >> x1 >> y1;
        if (sum(x0, y0) != sum(x1, y1)) { cout << -1 << endl; continue; }
        if (p == 2) { cout << 1 - (x0 == x1) << endl; continue; }
        int x_ = sum(x0, y0), y_ = sub(x0, y0), tgt = sub(x1, y1);
        if (y_ == tgt) { cout << 0 << endl; continue; }
        int ix_ = pw(x_, p - 2);
        for (int k = 0, rng = 1, i_rng = 1; ; k++, rng = rng * 2, i_rng = i_rng * inv2 % p) { // enumerate k - 1
            int val = sub(sum(tgt, x_) * inv2 % p, rng * y_ % p) * ix_ % p;
            if (val <= rng || p - val < rng) { cout << k + 1 << endl; break; }
        }
    }
}
