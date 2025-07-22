#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define seq(a, op, b) a = (a op b)

const int M = 998244353;
struct mint {
    int v = 0;
    mint() {}
    mint(int v) : v((v % M + M) % M) {}
    operator int() { return v; }
    mint operator+(const mint o) const { return v + o.v; }
    mint operator*(const mint o) const { return v * o.v; }
    mint operator-(const mint o) const { return v - o.v; }
    mint inv() {
        mint x = v, r = 1;
        for (int p = (M - 2) * 2; p >>= 1; x = x * x) if (p & 1) r = r * x;
        return r;
    }
};

const int N = 3e5 + 1;

int n, k, sz[N], fa[N];
mint p[N], cross[N][2];
array<int, 2> e[N];
vector<int> g[N];

int get_sz(int x, int p) {
    fa[x] = p;
    for (int i : g[x]) {
        auto &[u, v] = e[i];
        if (int nx = u ^ v ^ x; nx != p) sz[x] += get_sz(nx, x);
    }
    return sz[x];
}

int32_t main() {
   cin >> n >> k;
    for (int _ = 0; _ < k; _++) {
       int x; cin >> x;
       p[x] = sz[x] = 1;
    }

    auto i2 = mint{2}.inv();
    for (int i = 1; i < n; i++) {
        cin >> e[i][0] >> e[i][1];
        for (int t : {0, 1}) g[e[i][t]].push_back(i);
    }

    get_sz(1, 0);
    mint r = 0;
    for (int i = 1; i < n; i++) {
        int ch = (fa[e[i][0]] == e[i][1]) ? e[i][0] : e[i][1];
        array<mint, 2> s = {sz[ch], k - sz[ch]};
        if (ch == e[i][1]) swap(s[0], s[1]);
        for (int t : {0, 1}) {
            cross[i][t] = p[e[i][t]];
            mint c = cross[i][t] * (mint{1} - p[e[i][t ^ 1]]);
            seq(r, +, (c * (s[t] - mint{1}) * (s[t ^ 1] + mint{1}) + (mint{1} - c) * s[t] * s[t ^ 1]) * i2);
        }
        for (int t : {0, 1}) p[e[i][t]] = p[e[i][t]] * (cross[i][t ^ 1] + mint{1}) * i2 + (mint{1} - p[e[i][t]]) * cross[i][t ^ 1] * i2;
    }
    cout << r * mint{k * (k - 1) / 2}.inv() << endl;
}
