// https://codeforces.com/problemset/problem/981/G
#include <iostream>
using ll = long long;
const int M = 998244353;
const int N = 2e5 + 1;
ll d2(ll x) { return x * (M + 1) / 2 % M; }
struct seg {
    static seg* tot, cur;
    int l, r; // 1-indexed
    ll empty = 0, s = 0; // # of empty sets, total sum of sizes
    ll lazy = 1, totL = 1;
    seg *L = nullptr, *R = nullptr;
    seg(int l, int r, ll totl = 1) : l(l), r(r) {
        this->totL = totl;
        if (totL == 1) empty = r - l + 1;
        else s = d2(totl) * (r - l + 1) % M;
    }
    void push() {
        if (lazy == 1) return;
        s = (s * lazy + empty * d2(lazy)) % M;
        empty = 0;
        if (L) {
            L->lazy = L->lazy * lazy % M;
            L->totL = totL;
        }
        if (R) {
            R->lazy = R->lazy * lazy % M;
            R->totL = totL;
        }
        lazy = 1;
    }
    ll query(int ql, int qr) {
        push();
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return s;
        int m = (l + r) / 2;
        ll res = 0;
        if (ql <= m) {
            if (!L) L = new seg(l, m, totL);
            res += L->query(ql, qr);
        }
        if (qr > m) {
            if (!R) R = new seg(m + 1, r, totL);
            res += R->query(ql, qr);
        }
        return res % M;
    }
    void upd(int ql, int qr) {
        push();
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            lazy = lazy * 2 % M;
            totL = totL * 2 % M;
            push();
        } else {
            int m = (l + r) / 2;
            if (ql <= m) {
                if (!L) L = new seg(l, m, totL);
                L->upd(ql, qr);
            }
            if (qr > m) {
                if (!R) R = new seg(m + 1, r, totL);
                R->upd(ql, qr);
            }   
            empty = L->empty + R->empty;
        }
    }
};