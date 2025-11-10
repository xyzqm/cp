#include <bits/stdc++.h>
using namespace std;

#define int int64_t

__int128 GCD(__int128 a, __int128 b) {
    while (b != 0) tie(a, b) = make_pair(b, a % b);
    return a;
}

struct rat { __int128 a = 0, b = 1;
    void reduce() { __int128 g = GCD(a, b); a /= g, b /= g; }
};

rat operator+(rat a, rat b) {
    rat c = {a.a * b.b + a.b * b.a, a.b * b.b};
    c.reduce();
    return c;
}

rat operator*(rat a, rat b) {
    rat c = {a.a * b.a, a.b * b.b};
    c.reduce();
    return c;
}

rat operator/(rat a, rat b) {
    rat c = {a.a * b.b, a.b * b.a};
    c.reduce();
    return c;
}

ostream& operator<<(ostream& os, rat a) {
    return os << (int)a.a << "/" << (int)a.b;
}

int32_t main() {
    int n, m, k; cin >> n >> m >> k;
    --k;
    vector<rat> dp(1 << n);
    for (int i = 0; i < n; i++) dp[1 << i] = {1, n};
    while (m--) {
        int x, y; cin >> x >> y;
        --x, --y;
        for (int i = 1 << n; i --> 0; ) for (int _ : {0, 1}) {
            if (i >> x & 1 && !(i >> y & 1)) {
                rat nx = dp[i] * rat{1, 2};
                dp[i ^ (1 << y)] = dp[i ^ (1 << y)] + nx;
                dp[i] = nx;
            }
            swap(x, y);
        }
    }
    vector<rat> sm(n);
    for (int i = 0; i < 1 << n; i++) for (int j = 0; j < n; j++) if (i >> j & 1 && i >> k & 1) sm[j] = sm[j] + dp[i];
    for (int i = 0; i < n; i++) cout << sm[i] / sm[k] << endl;
}
