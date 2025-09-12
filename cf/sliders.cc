// https://codeforces.com/contest/2138/problem/D
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 1e9 + 7;

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

void ac() {
    int n, m, q; cin >> n >> m >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    auto qs = vector(q, array{0, 0});
    for (auto &[i, x] : qs) {
        cin >> i >> x;
        x -= i;
    }
    ranges::sort(qs, [](auto a, auto b) { return a[1] < b[1]; });
    vector<mint> invs(q + 1);
    for (int i = 1; i <= q; i++) invs[i] = mint{i}.inv();
    for (int i = 1; i <= n; i++) {
        array<vector<int>, 3> ops;
        for (auto [j, x] : qs) {
            if (i == j) ops[2].push_back(x + i);
            else ops[j < i].push_back(x + i);
        }
        vector<vector<int>::iterator> its(3);
        for (int i = 0; i < 3; i++) its[i] = ops[i].begin();
        int prv = 0;
        mint ans = 0;
        while (true) {
            int nx = m + 1;
            for (int i = 0; i < 3; i++) if (its[i] != ops[i].end()) nx = min(nx, *its[i]);
            if (a[i] && a[i] < nx) nx = a[i];
            if (nx == m + 1) break;
            int n_0 = (its[0] - ops[0].begin()) + (its[2] - ops[2].begin());
            int n_1 = (ops[1].end() - its[1]) + (ops[2].end() - its[2]);
            if (n_1) ans = ans + invs[n_0 + n_1] * n_1 * (nx - prv);
            else if (!n_0 && a[i] >= nx) ans = ans + (nx - prv);
            if (nx == a[i]) a[i] = 0;
            for (int i = 0; i < 3; i++) while (its[i] != ops[i].end() && *its[i] == nx) ++its[i];
            prv = nx;
        }
        for (int i = 1; i <= q; i++) ans = ans * i;
        cout << ans.v << " ";
    }
    cout << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
