#include <bits/stdc++.h>
using namespace std;

// #define EVAL
#ifdef EVAL
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t
#define ALL(v) v.begin(), v.end()

const int inf = 1e14;

int32_t main() {
    int n, m, L, q; cin >> n >> m >> L >> q;
    vector<int> t(m);
    for (int &x : t) {
        cin >> x;
        x += L;
    }
    DBG(t);
    vector<array<int, 4>> qs(q);
    vector<int> qt(q);
    for (int i = 0; auto &[rate, l, r, qi] : qs) {
        cin >> rate >> qt[qi = i];
        l = upper_bound(ALL(t), qt[qi]) - t.begin();
        r = upper_bound(ALL(t), qt[qi] + L) - t.begin();
        i++;
    }
    DBG(qs);
    sort(ALL(qs), greater()); // decreasing order of rate
    vector<int> res(q, inf);
    auto dnc = [&](auto self, int l, int r, vector<array<int, 4>> qs) -> void {
        DBG(l);
        DBG(r);
        DBG(qs);
        int m = (l + r) >> 1;
        vector<int> cht;
        auto ceil = [](int x, int y) { return x / y + ((x ^ y) > 0 && x % y); };
        auto isect = [&](int i, int j) { return ceil(t[j] - t[i], j - i); };
        auto useless = [&](int i, int j, int k) {
            return isect(j, k) <= isect(i, j);
        };
        for (int i = l; i < r; i++) {
            while (cht.size() > 1 && useless(cht[cht.size() - 2], cht.back(), i)) cht.pop_back();
            cht.push_back(i);
        }
        vector<array<int, 4>> lq, rq;
        for (auto &q : qs) {
            auto &[rate, ql, qr, qi] = q;
            if (ql <= l && r <= qr) {
                while (cht.size() > 1 && isect(cht[cht.size() - 2], cht.back()) > rate) cht.pop_back();
                res[qi] = min(res[qi], t[cht.back()] - cht.back() * rate);
            }
            else if (ql < qr) {
                if (ql < m) lq.push_back(q);
                if (qr > m) rq.push_back(q);
            }
        }
        if (lq.size()) self(self, l, m, lq);
        if (rq.size()) self(self, m, r, rq);
    };
    dnc(dnc, 0, m, qs);
    DBG(res);
    for (auto &[rate, ql, qr, qi] : qs) {
        res[qi] -= qt[qi];
        res[qi] += rate * (qr - 1);
        assert(res[qi] >= 0);
        res[qi] /= rate;
        res[qi] = min(res[qi], qr - ql);
    }
    DBG(res);
    for (int q : res) cout << q << "\n";
}
