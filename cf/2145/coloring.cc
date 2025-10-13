#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 998244353;

struct mint {
    int v = 0;
    mint() {}
    mint(int v) : v(v) {}
    mint operator*(mint o) { return v * o.v % M; }
    mint operator+(mint o) { return (v + o.v) % M; }
    void operator+=(mint o) { v = (v + o.v) % M; }
    mint operator-(mint o) { if (int x = v - o.v; x < 0) return x + M; else return x; }
    mint inv() {
        mint x = v, r = 1;
        for (int p = (M - 2) * 2; p >>= 1; x = x * x) if (p & 1) r = r * x;
        return r;
    }
};

int32_t main() {
    int n, m, k; cin >> n >> m >> k;
    auto binom = vector(max(n, m) + 2, vector<mint>(max(n, m) + 2));
    binom[0][0] = 1;
    for (int i = 0; i <= max(n, m); i++) for (int j = 0; j <= max(n, m); j++) {
        binom[i + 1][j] += binom[i][j];
        binom[i][j + 1] += binom[i][j];
    }
    auto sp = vector(n + m, vector<mint>(k));
    sp[0][0] = 1;
    for (int i = 1; i < n + m; i++) for (int j = 1; j < k; j++) {
        sp[i][j] = sp[i - 1][j - 1] * (k - j) + sp[i - 1][j] * j;
    }
    vector<mint> ans(n + m);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        ans[n + m - max(i, j)] += binom[n - i][i] * binom[m - j][j] * sp[n + m - i - j][k - 1];
    }
    for (int i = min(n, m); i < n + m; i++) cout << ans[i].v << " ";
    cout << endl;
}
