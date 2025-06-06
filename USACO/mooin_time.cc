#include <bits/stdc++.h>
using namespace std;

#define int int64_t

// min/+ convolution of convex functions
vector<int> merge(vector<vector<int>> fns) {
    vector<vector<int>::iterator> its(fns.size());
    for (int i = 0; i < fns.size(); i++) its[i] = fns[i].begin();
    auto at_end = [&](int i) { return next(its[i]) == fns[i].end(); };
    auto dif = [&](int i) { return *next(its[i]) - *its[i]; };

    vector<int> opt(fns.size()), ret(1);
    iota(opt.begin(), opt.end(), 0);
    auto nx = [&]() {
        return *min_element(opt.begin(), opt.end(), [&](int i, int j) {
            if (at_end(i) && at_end(j)) return i < j;
            if (at_end(i) || at_end(j)) return !at_end(i);
            else return dif(i) < dif(j);
        });
    };

    for (int i = nx(); !at_end(i); i = nx()) {
        ret.push_back(ret.back() + dif(i));
        ++its[i];
    }
    return ret;
}

void chmin(vector<int> &a, vector<int> &b) {
    for (int i = 0; i < min(a.size(), b.size()); i++) a[i] = min(a[i], b[i]);
    for (int i = a.size(); i < b.size(); i++) a.push_back(b[i]);
}

int L, n;
string s;

vector<int> c;
int cost(int i) {
    assert(i + L <= n);
    int r = 0;
    for (int j = i; j < i + L; j++) r += c[j] * ((s[j] == 'M') ^ (j == i));
    return r;
}

using T = array<array<vector<int>, 3>, 3>;
// solve range [l, r)
T solve(int l, int r) {
    T res;
    for (int i = 0; i < L; i++) for (int j = 0; j < L; j++) if (i + j <= r - l) res[i][j] = {0};
    if (r - l == 1 && L == 1) {
        res[0][0].push_back(cost(l));
        return res;
    }
    if (r - l < L) return res;

    int m = (l + r) >> 1;
    T lc = solve(l, m), rc = solve(m, r);
    for (int i = 0; i < L; i++) for (int j = 0; j < L; j++) if ((r - l) - (i + j) >= L) {
        res[i][j] = merge({lc[i][0], rc[0][j]});
        for (int k = 1; k < L; k++) if (m - k >= l + i && m + L - 1 - k < r - j) {
            auto f = merge({lc[i][k], rc[L - k][j], {0, cost(m - k)}});
            chmin(res[i][j], f);
        }
    }
    return res;
}

int32_t main() {
    cin >> L >> n >> s;
    c.resize(n);
    for (int &x : c) cin >> x;
    T res = solve(0, n);
    res[0][0].erase(res[0][0].begin());
    for (int &x : res[0][0]) cout << x << endl;
}
