#include <bits/stdc++.h>
using namespace std;

#define int int64_t

struct node { int sm = 0, mn = 0, mx = 0; };
node operator+(node a, node b) {
    return {a.sm + b.sm, min(b.mn, a.mn + b.sm), max(b.mx, a.mx + b.sm)};
}

struct sgt : vector<node> {
    int n;
    sgt(int n) : vector(4 * n), n(n) {}
    void upd(int i, node v) {
        auto u = [&](auto &&u, int p, int l, int r) -> void {
            if (r - l == 1) at(p) = v;
            else {
                int m = (l + r) >> 1;
                if (i < m) u(u, p << 1, l, m);
                else u(u, p << 1 ^ 1, m, r);
                at(p) = at(p << 1) + at(p << 1 ^ 1);
            }
        };
        u(u, 1, 0, n);
    }
    int walk(node v, function<bool(node)> &&f) { // find leftmost l s.t. f(sum[l, n) + v) = true
        auto w = [&](auto &&w, int p, int l, int r) -> int {
            if (f(at(p) + v)) return v = at(p) + v, l;
            else if (r - l == 1) return r;
            else {
                int m = (l + r) >> 1;
                if (int x = w(w, p << 1 ^ 1, m, r); x > m) return x;
                else return w(w, p << 1, l, m);
            }
        };
        return f(v) ? w(w, 1, 0, n) : n + 1;
    }
};

int32_t main() {
    int n, q, k; cin >> n >> q >> k;
    sgt t(q);
    int prv = 0;
    vector<array<int, 2>> qs;
    while (q--) {
        char c; int tt; cin >> c >> tt;
        int v = (c == '<' ? 1 : -1);
        t.upd((int)qs.size(), {v, v, v});
        qs.push_back({tt - prv, (int)qs.size()});
        prv = tt;
    }
    sort(qs.begin(), qs.end(), greater<>());
    node init = {0, 0, 0};
    auto check = [&]() {
        int t1 = t.walk(init, [&](node x) { return k + x.mn >= 1; }); // first time going under 1
        int t2 = t.walk(init, [&](node x) { return k + x.mx < n; }); // first time hitting n
        int t3 = t.walk(init, [&](node x) { return k + x.mn > 1; }); // first time hitting 1
        int t4 = t.walk(init, [&](node x) { return k + x.mx <= n; }); // first time going over n
        if (t1 <= t2 && t3 >= t4) {
            if (t[1].mx + k < n) return max(t[1].sm, -k) + k;
            else return n;
        }
        else return n + 1;
    };
    if (int x = check(); x <= n) cout << -1 << " " << x << endl;
    else for (auto it = qs.begin(); it != qs.end(); ) {
        int cur = (*it)[0];
        while (it != qs.end() && (*it)[0] == cur) {
            t.upd((*it++)[1], {0, 0, 0});
        }
        if (int x = check(); x <= n) {
            cout << cur - 1 << " " << x << endl;
            break;
        }
    }
}
