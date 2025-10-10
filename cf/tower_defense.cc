// https://codeforces.com/problemset/problem/1651/F
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define sz(X) (int)X.size()

// T[0] = sum of c, T[1] = sum of r
using T = array<int, 2>;
T id = {0, 0};
struct node { T v = id; array<int, 2> c = {0, 0}; };
const int mx = 2e12; // hopefully will prevent overflow
T operator+(T a, T b) { return {min(a[0] + b[0], mx), min(a[1] + b[1], mx)}; }

struct PST : vector<node> {
    int n;
    PST(int n) : vector(2), n(n) { reserve(70 * n); }
    int node(T v, array<int, 2> c = {0, 0}) { return push_back({v, c}), size() - 1; }
    int upd(int p, int i, T x) {
        auto u = [&](auto &&u, int p, int l, int r) -> int {
            auto [_, c] = at(p);
            if (r - l == 1) return node(x, c);
            else {
                int m = (l + r) >> 1;
                if (i < m) c[0] = u(u, c[0], l, m);
                else c[1] = u(u, c[1], m, r);
                return node(at(c[0]).v + at(c[1]).v, c);
            }
        };
        return u(u, p, 0, n);
    }
    array<int, 2> walk(int p, int ql, int qr, int tgt, function<int(T)> &&fn) { // finds max r s.t. sum of fn(data[ql...r)) <= tgt, asw as leftover
        auto w = [&](auto &&w, int p, int l, int r) -> int {
            auto [v, c] = at(p);
            if (!p || ql >= r || l >= qr) return ql;
            else if (int x = fn(v); ql <= l && r <= qr && x <= tgt) return tgt -= x, r;
            else if (r - l == 1) return ql;
            else {
                int m = (l + r) >> 1;
                int lw = w(w, c[0], l, m);
                return lw < m ? lw : max(lw, w(w, c[1], m, r));
            }
        };
        return {w(w, p, 0, n), tgt};
    }
};

int32_t main() {
    int n; cin >> n;
    vector<array<int, 3>> tws(n);
    PST pst(n);
    for (int i = 0; auto &[c, r, idx] : tws) {
        cin >> c >> r;
        pst.upd(sz(pst) - 1, idx = i++, {0, r});
    }
    auto og = tws;
    sort(tws.begin(), tws.end(), [](auto a, auto b) { return (a[0] + a[1] - 1) / a[1] < (b[0] + b[1] - 1) / b[1]; }); // sort by time taken to regenerate
    vector<array<int, 2>> psts;
    psts.push_back({0, sz(pst) - 1});
    for (auto &[c, r, i] : tws) {
        pst.upd(sz(pst) - 1, i, {c, 0});
        psts.push_back({(c + r - 1) / r, sz(pst) - 1});
    }
    struct sgt { int l, r, t, off = 0; };
    vector<sgt> sgts = {{0, n, -1, 0}};
    int q, ans = 0; cin >> q;
    while (q--) {
        int t, h; cin >> t >> h;
        while (h > 0 && sgts.size()) {
            auto &[l, r, t0, off] = sgts.back();
            if (l >= r) { sgts.pop_back(); continue; } // empty segment
            int p = t0 < 0 ? psts.back()[1] : (*--ranges::lower_bound(psts, array{t - t0 + 1, 0LL}))[1];
            if (off) assert(r - l == 1);
            auto val = [&](int i) { return t0 < 0 ? og[i][0] : min(og[i][0], off + (t - t0) * og[i][1]); };
            auto [mx_r, rem] = pst.walk(p, l, r, h, [&](T v) { return off ? val(l) : v[0] + (t - t0) * v[1]; });
            h = rem;
            if (mx_r < r || !h) {
                l = mx_r + (h > 0);
                if (h) sgts.push_back({mx_r, mx_r + 1, t, val(mx_r) - h});
                sgts.push_back({0, mx_r, t, 0});
                h = 0;
            }
            else sgts.pop_back();
        }
        if (!sgts.size()) sgts.push_back({0, n, t, 0});
        ans += h;
    }
    cout << ans << endl;
}
