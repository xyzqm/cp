#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int inf = 1e15;

using fn = vector<int>;
// convolve two convex functions
fn operator+(fn a, fn b) {
    if (!a.size()) return b;
    if (!b.size()) return a;
    adjacent_difference(a.begin(), a.end(), a.begin());
    adjacent_difference(b.begin(), b.end(), b.begin());
    assert(is_sorted(a.begin() + 1, a.end(), greater<int>()));
    assert(is_sorted(b.begin() + 1, b.end(), greater<int>()));
    vector<int> res = {a[0] + b[0]};
    merge(a.begin() + 1, a.end(), b.begin() + 1, b.end(), back_inserter(res), greater<int>());
    partial_sum(res.begin(), res.end(), res.begin());
    return res;
}

void smax(int &a, int b) { a = max(a, b); }

void smax(fn &a, fn b) {
    if (a.size() < b.size()) a.swap(b);
    for (int i = 0; i < b.size(); i++) smax(a[i], b[i]);
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int> v = {0};
    while (n --> 0) {
        int b, len; cin >> b >> len;
        if (b == (v.size() & 1)) v.push_back(len);
        else v.back() += len;
    }
    if (v.size() & 1) v.push_back(0);

    using info = array<array<fn, 2>, 2>;
    auto dp = [&](int l, int r, auto &&f) -> info {
        assert(l < r);
        info res;
        if (r - l == 1) {
            for (int in : {0, 1}) for (int out : {0, 1}) {
                res[in][out] = {0, 0};
                if (in == 1 && out == 0) res[in][out] = {-inf, 0};
                res[in][out][(in > (l & 1)) + ((l & 1) > out)] = v[l];
                smax(res[in][out][1], res[in][out][0]);
            }
        }
        else {
            int m = (l + r) >> 1;
            info L = f(l, m, f);
            info R = f(m, r, f);
            for (int in : {0, 1}) for (int mid : {0, 1}) for (int out : {0, 1}) {
                smax(res[in][out], L[in][mid] + R[mid][out]);
            }
        }
        return res;
    };

    auto res = dp(0, v.size(), dp);
    DBG(res);
    int m; cin >> m;
    for (int i = 0; i <= m; i++) cout << res[0][1][i] << endl;
}
