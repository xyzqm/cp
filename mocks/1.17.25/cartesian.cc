#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int N = 5e5 + 1;
int sgt[4 * N], lz[4 * N], n;

void apply(int p, int pl, int pr, int x) {
    sgt[p] += (pr - pl) * x;
    if (pr > pl + 1) lz[p] += x;
}

void push(int p, int pl, int pr) {
    if (lz[p]) {
        int pm = (pl + pr) >> 1;
        apply(p << 1, pl, pm, lz[p]);
        apply(p << 1 | 1, pm, pr, lz[p]);
        lz[p] = 0;
    }
}

void pull(int p) {
    assert(!lz[p]);
    sgt[p] = sgt[p << 1] + sgt[p << 1 | 1];
}

void inc(int l, int r, int x, int p = 1, int pl = 0, int pr = n) {
    if (r <= pl || pr <= l) return;
    else if (l <= pl && pr <= r) apply(p, pl, pr, x);
    else {
        assert(pr > pl + 1);
        push(p, pl, pr);
        int pm = (pl + pr) >> 1;
        inc(l, r, x, p << 1, pl, pm);
        inc(l, r, x, p << 1 | 1, pm, pr);
        pull(p);
    }
}

int query(int l, int r, int p = 1, int pl = 0, int pr = n) {
    if (l <= pl && pr <= r) return sgt[p];
    else if (r <= pl || pr <= l) return 0;
    else {
        assert(pr > pl + 1);
        push(p, pl, pr);
        int pm = (pl + pr) >> 1;
        return query(l, r, p << 1, pl, pm) + query(l, r, p << 1 | 1, pm, pr);
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int q; cin >> n >> q;
    vector<int> p(n);
    for (int &x : p) cin >> x;
    vector<vector<array<int, 2>>> qs(n + 1);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        qs[r].push_back({--l, i});
    }
    vector<int> res(q), stk;
    int ad = 0;
    for (int r = 0; r <= n; r++) {
        for (auto [l, i] : qs[r]) {
            assert(stk.size());
            auto it = lower_bound(stk.begin(), stk.end(), l);
            assert(it != stk.end());
            int rem = stk.end() - it;
            res[i] = query(l, r) + rem * ad + (r - l);
        }
        if (r == n) break;
        while (stk.size() && p[r] < p[stk.back()]) {
            inc(stk.back(), stk.back() + 1, ad);
            stk.pop_back();
        }
        ++ad;
        inc(stk.size() ? stk.back() + 1 : 0, r, 1);
        inc(r, r + 1, -ad);
        stk.push_back(r);
    }
    for (int i = 0; i < q; i++) cout << res[i] << "\n";
}
