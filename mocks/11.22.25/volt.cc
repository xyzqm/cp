#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 998244353;

inline void mul(int &a, const int b) { a = a * b % M; }
inline void ad(int &a, const int b) { a = (a + b) % M; }
int exp(int x, int y) {
    int r = 1;
    for (; y; y >>= 1, mul(x, x)) if (y & 1) mul(r, x);
    return r;
}

struct edge {
    int v; bool out; // whether edge to v is an out edge
};

using vec = vector<int>;
// pointwise addition
vec operator+(vec a, vec b) {
    if (a.size() < b.size()) a.swap(b);
    for (int i = 0; i < b.size(); i++) ad(a[i], b[i]);
    return a;
}
// convolve
vec conv(vec a, vec b, int off, int m) {
    vec c(a.size() + b.size() - 1 + off);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) if (i + j + off >= 0) ad(c[i + j + off], (M + (a[i] * b[j] % M) * m) % M);
    }
    return c;
}

int32_t main() {
    int n; cin >> n;
    // precomp factorials
    vector<int> fac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % M;

    vector<vector<edge>> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back({v, true});
        g[v].push_back({u, false});
    }
    auto dp = vector(n + 1, array<vec, 4>{{{0}, {0}, {0}, {0}}}); // [n][4][rem + k]
    auto dfs = [&](auto &&f, int x, int p) -> void {
        dp[x][0]  = {0, 1}; // no edges in or out
        for (auto [y, out] : g[x]) if (y != p) {
            f(f, y, x);
            vec tot;
            for (int i = 0; i < 4; i++) tot = tot + dp[y][i];
            array<vec, 4> nx{};
            // make no new connections
            for (int i = 0; i < 4; i++) nx[i] = nx[i] + conv(dp[x][i], tot, 0, 1);
            if (out) { // plug in an out edge
                for (int cur : {0b00, 0b10}) nx[cur ^ 0b01] = nx[cur ^ 0b01] + conv(dp[x][cur], dp[y][0b01] + dp[y][0b00], -1, -1);
            }
            else { // plug in an in edge
                for (int cur : {0b00, 0b01}) nx[cur ^ 0b10] = nx[cur ^ 0b10] + conv(dp[x][cur], dp[y][0b10] + dp[y][0b00], -1, -1);
            }
            dp[x].swap(nx);
        }
    };
    dfs(dfs, 1, 0);
    int res = 0;
    for (auto &v : dp[1]) for (int i = 0; i < v.size(); i++) ad(res, fac[i] * v[i] % M);
    cout << res << endl;
}
