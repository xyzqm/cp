#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int N = 3e5 + 1;
const int inf = 1e15;

int sgt[4 * N], lz[4 * N];

void push(int p, int l, int r) {
    // DBG(p);
    // DBG(l);
    // DBG(r);
    sgt[p] += lz[p] * (r - l);
    if (r - l > 1) {
        lz[p << 1] += lz[p];
        lz[p << 1 | 1] += lz[p];
    }
    lz[p] = 0;
}

void upd(int l, int r, int v, int p = 1, int pl = 0, int pr = N) {
    push(p, pl, pr);
    if (r <= pl || l >= pr) return;
    else if (l <= pl && pr <= r) lz[p] += v, push(p, pl, pr);
    else {
        int m = (pl + pr) >> 1;
        upd(l, r, v, p << 1, pl, m);
        upd(l, r, v, p << 1 | 1, m, pr);
        sgt[p] = sgt[p << 1] + sgt[p << 1 | 1];
    }
}

int query(int l, int r, int p = 1, int pl = 0, int pr = N) {
    push(p, pl, pr);
    if (r <= pl || l >= pr) return 0;
    else if (l <= pl && pr <= r) return sgt[p];
    else {
        int m = (pl + pr) >> 1;
        return query(l, r, p << 1, pl, m) + query(l, r, p << 1 | 1, m, pr);
    }
}


struct itv {
    int l, r;
    int first, last;
};

#ifdef ONLINE_JUDGE
void disp(itv iv) {}
#else
void disp(itv iv) {
    auto [l, r, first, last] = iv;
    cout << l << ":" << r << " " << first << ":" << last << endl;
}
#endif

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, d; cin >> n >> d;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    int q; cin >> q;
    vector<vector<array<int, 2>>> qs(n + 1);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        qs[--r].push_back({--l, i});
    }
    auto dec = [&](itv iv, int val) { // decrement itv until itv.last <= val
        if (iv.last <= val) return iv;
        int steps = (iv.last - val + d - 1) / d;
        upd(iv.l, iv.r, steps);
        return itv{iv.l, iv.r, iv.first - steps * d, iv.last - steps * d};
    };
    auto mg = [&](itv l, itv r) {
        // disp(l);
        // disp(r);
        assert(l.r == r.l && l.last <= r.first && r.first - l.last < d);
        return itv{l.l, r.r, l.first, r.last};
    };
    vector<itv> stk;
    vector<int> res(q);
    int l_nneg = 0;
    for (int r = 0; r < n; r++) {
        itv cur = {r, r + 1, a[r], a[r]};
        while (stk.size() && stk.back().last > cur.first) {
            cur = mg(dec(stk.back(), cur.first), cur);
            stk.pop_back();
        }
        if (cur.first < 0) {
            assert(!stk.size());
            while (a[cur.l] - query(cur.l, cur.l + 1) * d < 0) l_nneg = ++cur.l;
            cur.first = a[cur.l] - query(cur.l, cur.l + 1) * d;
        }
        stk.push_back(cur);
        for (auto &iv : stk) {
            disp(iv);
        }
        for (int i = 0; i < r; i++) DBG(query(i, i + 1));
        DBG("done");
        for (auto &[l, qi] : qs[r]) res[qi] = l >= l_nneg ? query(l, r + 1) : -1;
    }
    for (int i = 0; i < q; i++) cout << res[i] << endl;
}
