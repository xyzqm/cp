#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 1e9 + 7;

int C2(int x) { return x * (x - 1) % M * 500000004 % M; }
int C3(int x) { return x * (x - 1) * (x - 2) % M * 166666668 % M; }

int sb(int x, int y, int M = ::M) {
    int v = x - y;
    return v < 0 ? v + M : v;
}

int n;
struct seg {
    int l, r; // range [l, r)
    bool cross;
    bool full() {
        return r - l == n || (cross && (r + n - l) >= n);
    }
    int val() {
        if (!cross) return C3(r - l);
        else {
            return (C3(n - l) + C3(r) + C3(min(r - 1, n - l))) % M;
        }
    }
    int merge(seg &o) {
        if (o.l != (r % n)) return 0;
        // assert(o.l == (r % n));
        int res = 2 * M - val() - o.val();
        if (r == n) cross = true;
        r = o.r;
        o = *this;
        return res = val() % M;
    }
};

int32_t main() {
    cin >> n;
    vector<array<int, 2>> vals(n);
    for (int i = 0; i < n; i++) {
        cin >> vals[i][0];
        vals[i][1] = i;
    }
    sort(vals.begin(), vals.end());
    vector<int> st(n, 1);
    vector<seg> sgts(n);
    auto upd = [&](seg s) { sgts[s.l] = sgts[s.r] = s; };
    for (int i = 0; i < n; i++) sgts[i] = {i, i, 0};
    int bad = 0, tot = C2(C2(n + 1) + 1), res = 0, lst = 0;
    for (auto [v, i] : vals) {
        // println("{} {} {} {}", tot, bad, res, lst);
        if (v != lst) res = (res + sb(tot, bad) * (v - lst)) % M;
        lst = v;
        st[i] = 0, sgts[i] = {i, i + 1, 0}, ++bad;
        bad += sgts[sb(i, 1, n)].merge(sgts[i]);
        bad += sgts[i].merge(sgts[(i + 1) % n]);
        bad %= M;
        if (bad < 0) bad += M;
        upd(sgts[i]);
    }
    cout << res << endl;
}
