// https://codeforces.com/contest/2145/problem/E
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

struct dat { int sm = 0, min_sm = 0;
    void operator+=(int dif) { sm += dif, min_sm += dif; }
};
dat operator+(dat l, dat r) { return {l.sm + r.sm, min(l.min_sm, l.sm + r.min_sm) }; };
struct sgt : vector<dat> {
    int n;
    sgt(int n) : vector(2 * n), n(n) {}
    void upd(int i, int dif) {
        for (at(i += n) += dif; i >>= 1; ) at(i) = at(i << 1) + at(i << 1 | 1);
    }
    int walk() {
        int l = 0, tgt = 0; // want to find first sum < tgt
        for (l += n; l && at(l).min_sm >= tgt; l >>= 1) {
            if (l & 1) tgt -= at(l++).sm;
        }
        if (at(l).min_sm >= tgt) return n;
        else while (l < n) {
            if (at(l << 1).min_sm < tgt) l <<= 1;
            else tgt -= at(l << 1).sm, l = l << 1 | 1;
        }
        return l - n;
    }
};

const int MX = 2e6 + 1;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int ac, dr; cin >> ac >> dr;
    auto val = [&](int a, int d) { return max(a - ac, 0LL) + max(d - dr, 0LL); };
    int n; cin >> n;
    vector<int> a(n), d(n);
    for (int &x : a) cin >> x;
    for (int &x : d) cin >> x;
    sgt t(MX);
    for (int i = 0; i < MX; i++) t.upd(i, -1);
    for (auto [a, d] : views::zip(a, d)) t.upd(val(a, d), 1);
    int q; cin >> q;
    while (q--) {
        int i, na, nd; cin >> i >> na >> nd; --i;
        t.upd(val(a[i], d[i]), -1);
        t.upd(val(a[i] = na, d[i] = nd), 1);
        cout << t.walk() << endl;
    }
}
