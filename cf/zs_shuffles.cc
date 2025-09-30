#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 998244353;

struct mint {
    int v = 0;
    mint() {}
    mint(int v) : v(v) {}
    mint operator*(mint o) { return {v * o.v % M}; }
    mint operator+(mint o) { return {(v + o.v) % M}; }
    mint operator-(mint o) { if (int x = v - o.v; x < 0) return x + M; else return x; }
    mint inv() {
        mint x = v, r = 1;
        for (int p = (M - 2) * 2; p >>= 1; x = x * x) if (p & 1) r = r * x;
        return r;
    }
};
int32_t main() {
    int n, m; cin >> n >> m;
    vector<mint> F = {1}, i_F;
    for (int _ = n; _ --> 0; ) F.push_back(F.back() * F.size());
    i_F.resize(n + 1);
    i_F.back() = F.back().inv();
    for (int i = n; i --> 0; ) i_F[i] = i_F[i + 1] * (i + 1);
    auto binom = [&](int n, int i) { return F[n] * i_F[n - i] * i_F[i]; };
    mint sm = 0, mul = 1;
    for (int i = 1; i <= n; i++) {
        sm = sm + mul * binom(n, i) * (i + m) * mint{i}.inv();
        mul = mul * (M - 1);
    }
    cout << (sm * (mint{m + 1}.inv() * n + 1)).v << endl;
}
