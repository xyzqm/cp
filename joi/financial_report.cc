#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

struct dsu : vector<int> {
    dsu(int n) : vector(n, -1) {}
    int rep(int x) { return at(x) < 0 ? x : (at(x) = rep(at(x))); }
    bool join(int x, int y) { // unite to smaller x, NOT by size
        x = rep(x), y = rep(y);
        if (x == y) return false;
        if (x > y) ::swap(x, y);
        at(x) += at(y);
        at(y) = x;
        return true;
    }
};

struct sgt : vector<int> {
    int n;
    sgt(int n) : vector(2 * n), n(n) {}
    void upd(int &x, int v) { x = max(x, v); }
    void upd(int l, int r, int v) { // chmax [l, r) with v
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) upd(at(l++), v);
            if (r & 1) upd(at(--r), v);
        }
    }
    int get(int i) {
        int res = 0;
        for (i += n; i; i /= 2) upd(res, at(i));
        return res;
    }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, d; cin >> n >> d;
    vector<int> a(n), r(n);
    map<int, vector<int>> vals;
    for (int i = 0; int &x : a) {
        cin >> x;
        vals[x].push_back(i++);
    }
    dsu uf(n);
    set<int> cut = {n};
    for (auto it = vals.rbegin(); it != vals.rend(); it++) {
        DBG(cut);
        auto &[val, idx] = *it;
        DBG(idx);
        for (int i : idx) r[i] = *cut.upper_bound(i);
        for (int i : idx) {
            if (i && a[i - 1] >= val) uf.join(i - 1, i);
            if (i + 1 < n && a[i + 1] >= val) uf.join(i, i + 1);
            if (uf[uf.rep(i)] <= -d) cut.insert(uf.rep(i) + d);
        }
    }
    DBG(r);
    sgt sg(n);
    for (auto &[val, idx] : vals) {
        vector<int> cur(idx.size());
        for (int i = 0; i < idx.size(); i++) cur[i] = sg.get(idx[i]);
        for (auto [cur, i] : views::zip(cur, idx)) {
            sg.upd(i, r[i], cur + 1);
        }
    }
    DBG(sg);
    cout << sg.get(n - 1) << "\n";
}
