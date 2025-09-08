#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int inf = 1e10;

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
    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    lct lc(n);
    vector<int> mn = {-1};
    int cur = 0;
    for (int i = 0; i < n; i++) {
        while (mn.back() >= 0 && a[i] < a[mn.back()]) {
            int x = mn.back();
            mn.pop_back();
            cur -= (x - mn.back()) * (a[x] + 1) - 1;
        }
        cur += (i - mn.back()) * (a[i] + 1) - 1;
        mn.push_back(i);
        lc.upd({cur - (a[i] + 2) * i, a[i] + 2});
        print("{} ", lc.query(i));
    }
    println();
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
