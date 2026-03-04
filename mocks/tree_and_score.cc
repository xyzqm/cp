#include <bits/stdc++.h>
using namespace std;

#define int int64_t

struct bit : vector<int> {
    bit(int n) : vector(n + 1) {}
    void upd(int i, int x) { // increment index i by x
        for (++i; i < size(); i += i & -i) at(i) += x;
    }
    int query(int r) { // sum [0, r)
        int val = 0;
        for (; r; r -= r & -r) val += at(r);
        return val;
    }
    int query_suf(int l) { return query(size() - 1) - query(l); }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    auto a = vector(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];

    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    g[0] = {1};
    vector<int> par(n + 1), contr(n + 1);
    auto vals = vector(n + 1, vector<int>());
    auto solve = [&](auto &&f, int x, int p) -> void {
        vals[par[x] = p].push_back(a[x]);
        vals[x].push_back(a[x]);
        for (int y : g[x]) if (y != p) {
            if (a[y] > a[x]) contr[x] += a[y] - a[x];
            f(f, y, x);
        }
    };
    solve(solve, 0, 0);
    int cur = accumulate(contr.begin(), contr.end(), (int)0);
    vector<array<int, 2>> qs(q);
    for (auto &[x, v] : qs) {
        cin >> x >> v;
        vals[par[x]].push_back(v);
        vals[x].push_back(v);
    }
    for (auto &vs : vals) sort(vs.begin(), vs.end());
    vector<bit> bits(n + 1, bit(0));
    vector<bit> cnts(n + 1, bit(0));
    for (int i = 0; i <= n; i++) {
        cnts[i] = bits[i] = bit(vals[i].size());
    }
    auto compr = [&](int x, int val) {
        return lower_bound(vals[x].begin(), vals[x].end(), val) - vals[x].begin();
    };
    auto upd = [&](int x, int val, int mul) { // update bit[x] by adding mul copies of val
        int idx = compr(x, val);
        bits[x].upd(idx, val * mul);
        cnts[x].upd(idx, mul);
    };
    auto sync = [&](int x) { // sync x with its children
        int idx = compr(x, a[x]);
        int n_contr = bits[x].query_suf(idx) - cnts[x].query_suf(idx) * a[x];
        cur += n_contr - contr[x];
        contr[x] = n_contr;
    };
    for (int i = 1; i <= n; i++) upd(par[i], a[i], 1);
    for (auto &[x, v] : qs) {
        upd(par[x], a[x], -1);
        upd(par[x], a[x] = v, 1);
        sync(x);
        sync(par[x]);
        cout << cur << "\n";
    }
}
