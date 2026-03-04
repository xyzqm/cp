#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

template <class F>
struct sgt : vector<int> {
    int n, id;
    F op;
    sgt(int n, F op, int id) : vector(2 * n, id), n(n), id(id), op(op) {}
    void upd(int i, int x) {
        for (at(i += n) = x; i > 1; i >>= 1) {
            at(i >> 1) = op(at(i), at(i ^ 1)); // MUST BE COMMUTATIVE
        }
    }
    int query(int l, int r) { // gets product of range [l, r)
        int res = id;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = gcd(res, at(l++));
            if (r & 1) res = gcd(res, at(--r));
        }
        return res;
    }
    int walk(int l, int r, const auto &pred) { // first value m in [l, r) such that pred(prod[l...m)) is false
       int cur = 0;
        while (l < r) {
            int u = l + n, x = __lg(min(r - l, u & -u));
            if (int nx = op(cur, at(u >> x)); pred(nx)) l += 1 << x, cur = nx;
            else r = l + (1 << x) - 1;
        }
        return l;
    }
    int klaw(int l, int r, const auto &pred) { // last value m in (l, r] such that pred(prod(m...r]) is false
       int cur = 0;
        while (l < r) {
            int u = r + n, x = __lg(min(r - l, ~u & -(~u)));
            if (int nx = op(cur, at(u >> x)); pred(nx)) r -= 1 << x, cur = nx;
            else l = r - (1 << x) + 1;
        }
        return r;
    }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    sgt sg = sgt(n, [](int x, int y) { return gcd(x, y); }, 0);
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        sg.upd(i, x);
    }
    while (q--) {
        int i, v; cin >> i >> v;
        sg.upd(--i, v);
        // first, find splitting point
        int m = 0;
        for (int dif = n; dif > 0; dif >>= 1) {
            while (m + dif < n && sg.query(0, m + dif) > sg.query(m + dif, n)) m += dif;
        }
        DBG(m);
        int res = 0;
        // sum ranges starting from 0
        int acc = sg.query(0, m), cur = m;
        // DBG(pref);
        while (cur < n - 1) {
            int nx = sg.walk(cur, n - 1, [&](int v) { return gcd(acc, v) == acc; });
            // DBG(cur);
            // DBG(nx);
            res += (nx - cur) * acc;
            acc = sg.query(0, (cur = nx) + 1);
        }
        DBG(res);
        // sum ranges starting from n
        acc = sg.query(m, n), cur = m;
        while (cur) {
            int nx = sg.klaw(0, m, [&](int v) {return gcd(acc, v) == acc; });
            res += (cur - nx) * acc;
            acc = sg.query(cur = nx, n);
        }
        DBG(res);
        res += sg.query(0, n);
        cout << res << "\n";
    }
}
