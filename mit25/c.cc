#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int M = 1e9 + 7;

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

mint i_2 = mint{2}.inv();

void ac() {
    int n, K, q; cin >> n >> K >> q;
    vector<vector<array<int, 2>>> l(n + 1);
    auto r = l;
    while (q--) {
        int d, x, y, c; cin >> d >> x >> y >> c;
        l[x].push_back({d, c});
        r[y].push_back({d, c});
    }

    // trie
    vector<int> cnt(1);
    vector<mint> tot(1);
    vector<array<int, 2>> c(1);
    auto upd = [&](auto &&f, int x, mint color, int dif, int u = 0, int k = 59) -> mint {
        if (k < 0) {
            return tot[u] = (dif == 1 ? color : 0);
        }
        int b = x >> k & 1;
        if (!c[u][b]) c[u][b] = cnt.size(), cnt.push_back(0), c.push_back({0, 0}), tot.push_back(0);
        f(f, x, color, dif, c[u][b], k - 1);
        cnt[c[u][b]] += dif;
        mint r = 0;
        for (int t : {0, 1}) r = r + tot[c[u][t]] * (cnt[c[u][t ^ 1]] ? i_2 : 1);
        if (u) tot[u] = r;
        return r;
    };

    mint ans = 0, cur = 0;
    for (int i = 1; i <= n; i++) {
        for (auto [d, c] : l[i]) {
            cur = upd(upd, d, c, 1);
        }
        ans = ans + cur;
        for (auto [d, c] : r[i]) {
            cur = upd(upd, d, c, -1);
        }
    }
    while (K--) ans = ans * 2;
    cout << ans.v << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
