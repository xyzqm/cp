// range sum + range query
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5;
int n;
ll sum[4 * N], lazy[4 * N];
void push(int p, int l, int r) {
    if (lazy[p]) {
        if (l != r) {
            lazy[2 * p] += lazy[p];
            lazy[2 * p + 1] += lazy[p];
        }
        sum[p] += (r - l + 1) * lazy[p];
        lazy[p] = 0;
    }
}
ll _query(int p, int l, int r, int i, int j) {
    push(p, l, r);
    if (r < i || l > j) return 0;
    if (i <= l && r <= j) return sum[p];
    int m = (l + r) / 2;
    return _query(2 * p, l, m, i, j) + _query(2 * p + 1, m + 1, r, i, j);
}
ll query(int l, int r) {
    return _query(1, 1, n, l, r);
}
void _update(int p, int l, int r, int ql, int qr, int x) {
    push(p, l, r);
    if (l > qr || r < ql) return;
    if (ql <= l && r <= qr) {
        lazy[p] += x;
        push(p, l, r);
    }
    else {
        int m = (l + r) / 2;
        _update(2 * p, l, m, ql, qr, x);
        _update(2 * p + 1, m + 1, r, ql, qr, x);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
}
void update(int i, int j, int x) {
    return _update(1, 1, n, i, j, x);
}
int main() {
    int t; cin >> t;
    while (t--) {
        int c; cin >> n >> c;
        fill(sum, sum + 4 * n + 1, 0ll);
        fill(lazy, lazy + 4 * n + 1, 0ll);
        while (c--) {
            int op; cin >> op;
            if (op == 0) {
                int l, r, x; cin >> l >> r >> x;
                update(l, r, x);
            } else {
                int l, r; cin >> l >> r;
                cout << query(l, r) << endl;
            }
        }
    }
}