#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 0;
const int inf = 1e18; // CHANGE FOR SPECIFIC PROBLEM

struct mint {
    int v = 0;
    mint() {}
    mint(int v) : v((v % M + M) % M) {}
	operator int() { return v; }
    mint inv() {
        mint x = v, r = 1;
        for (int p = (M - 2) * 2; p >>= 1; x = x * x) if (p & 1) r = r * x;
        return r;
    }
};

template <typename F>
struct BIT : vector<int> {
    F op;
    int id;
    BIT(int n, int id, F f) : vector(n + 1, id), op(f), id(id) {}
    void upd(int i, int v) { // updates index i by value v
        for (++i; i < size(); i += i & -i) at(i) = op(at(i), v);
    }

    int query(int r) { // query op([0...r))
        int v = id;
        for (; r; r -= r & -r) v = op(v, at(r));
        return v;
    }

    int walk(int v) { // find largest r s.t. op([0...r)) < v
        int r = 0, cur = id;
        for (int k = __lg(size()); v > 0 && r < size(); k--) {
            if (int nr = r + (1 << k); nr < size() && op(cur, at(nr)) < v) cur = op(cur, at(nr));
        }
        return r;
    }
};

template <typename T>
vector<int> kmp(T s, T p) {
    vector<int> pre(p.size() + 1);
    for (int i = 1; i < p.size(); i++) {
        int j = pre[i];
        while (j && p[j] != p[i]) j = pre[j];
        pre[i + 1] = j + (p[j] == p[i]);
    }
    vector<int> kmp(s.size() + 1);
    for (int i = 0; i < s.size(); i++) {
        int j = kmp[i];
        while (j && p[j] != s[i]) j = pre[j];
        kmp[i + 1] = j + (p[j] == s[i]);
    }
    return kmp;
}

struct line {
    int b = inf, m = inf;
    int operator()(int x) { return b + m * x; }
};

struct lct : vector<line> {
    int n;
    lct(int n) : vector(4 * n), n(n) {}
    void upd(line ln, int p = 1, int l = 0, int r = -1) {
        if (r == -1) r = n;
        int m = (l + r) >> 1;
        if (ln(m) < at(p)(m)) ::swap(ln, at(p));
        if (r - l == 1) return;
        if (at(p)(l) > ln(l)) upd(ln, 2 * p, l, m);
        else upd(ln, 2 * p + 1, m, r);
    }
    int query(int x, int p = 1, int l = 0, int r = -1) {
        if (r == -1) r = n;
        if (r - l == 1) return at(p)(x);
        int m = (l + r) >> 1;
        return min(at(p)(x), (x < m ? query(x, 2 * p, l, m) : query(x, 2 * p + 1, m, r)));
    }
};

void ac() {

}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
