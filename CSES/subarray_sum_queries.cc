#pragma GCC optimize ("O3")
#include <iostream>
#include <climits>
using namespace std;
using ll = long long;
const int N = 2e5 + 1;
const ll inf = 1e18;
int n, m, a[N];
struct Data {
    ll sum = -inf, pre = -inf, suf = -inf, any = -inf;
} seg[4 * N];
// ostream& operator<<(ostream& os, const Data& d)
// {
//     os << d.sum << '/' << d.pre << '/' << d.suf << '/' << d.any;
//     return os;
// }

void upd(int& a, int b) {
    a = max(a, b);
}
Data _query(int p, int l, int r, int i, int j) {
    int m = (l + r) / 2;
    Data ans;
    if (l == i && r == j) ans = seg[p];
    else {
        Data lhs, rhs;
        if (i <= m) lhs = _query(2 * p, l, m, i, min(m, j));
        if (m < j) rhs = _query(2 * p + 1, m + 1, r, max(m + 1, i), j);
        ans.any = max(max(lhs.any, rhs.any), lhs.suf + rhs.pre);
        ans.pre = ((lhs.sum != -inf) ? max(lhs.pre, lhs.sum + rhs.pre) : rhs.pre);
        ans.suf = ((rhs.sum != -inf) ? max(rhs.suf, rhs.sum + lhs.suf) : lhs.suf);
        ans.sum = (i <= m) * lhs.sum + (m < j) * rhs.sum;
    }
    // cout << p << " " << l << " " << r << " " << i << " " << j << " " << ans << endl;
    return ans;
}
ll query(int l, int r) {
    return _query(1, 1, n, l, r).any;
}
void _update(int p, int l, int r, int i, int x) {
    if (l == r) seg[p] = {x, x, x, x};
    else {
        int m = (l + r) / 2;
        if (i <= m) _update(2 * p, l, m, i, x);
        else _update(2 * p + 1, m + 1, r, i, x);
        seg[p] = {
            seg[2 * p].sum + seg[2 * p + 1].sum,
            max(seg[2 * p].pre, seg[2 * p].sum + seg[2 * p + 1].pre),
            max(seg[2 * p + 1].suf, seg[2 * p].suf + seg[2 * p + 1].sum),
            max(seg[2 * p].suf + seg[2 * p + 1].pre, max(seg[2 * p].any, seg[2 * p + 1].any))
        };
    }
}
void update(int i, int x) {
    return _update(1, 1, n, i, x);
}
void _build(int p, int l, int r) {
    if (l == r) seg[p] = {a[l], a[l], a[l], a[l]};
    else {
        int m = (l + r) / 2;
        _build(2 * p, l, m); 
        _build(2 * p + 1, m + 1, r);
        seg[p] = {
            seg[2 * p].sum + seg[2 * p + 1].sum,
            max(seg[2 * p].pre, seg[2 * p].sum + seg[2 * p + 1].pre),
            max(seg[2 * p + 1].suf, seg[2 * p].suf + seg[2 * p + 1].sum),
            max(seg[2 * p].suf + seg[2 * p + 1].pre, max(seg[2 * p].any, seg[2 * p + 1].any))
        };
    }
}
void build() {
    _build(1, 1, n);
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build();
    while (m--) {
        int i, x;
        cin >> i >> x;
        update(i, x);
        cout << query(1, n) << endl;
        // else cout << query(y - 1, z - 1) << endl;
    }
}