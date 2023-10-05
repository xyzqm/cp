#include <iostream>
using namespace std;
using ll = long long;
const int N = 2e5 + 1;
ll seg[4 * N], lazy[4 * N], a[N];
int n, q;
void push(int p, int l, int r) {
    if (lazy[p]) {
        seg[p] += (r - l + 1) * lazy[p];
        if (l != r) {
            lazy[2 * p] += lazy[p];
            lazy[2 * p + 1] += lazy[p];
        }
        lazy[p] = 0;
    }
}
ll query(int i, int j, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if (l > j || r < i) return 0;
    else if (i <= l && r <= j) {
        return seg[p];
    }
    else {
        int m = (l + r) / 2;
        return query(i, j, 2 * p, l, m) + query(i, j, 2 * p + 1, m + 1, r);
    }
}
void update(int i, int j, ll x, int p = 1, int l = 1, int r = n) {
    push(p, l, r);
    if (l > j || r < i) return;
    else if (i <= l && r <= j) {
        lazy[p] += x;
        push(p, l, r);
    } else {
        int m = (l + r) / 2;
        update(i, j, x, 2 * p, l, m);
        update(i, j, x, 2 * p + 1, m + 1, r);
        seg[p] = seg[2 * p] + seg[2 * p + 1];
    }
}
void build(int p = 1, int l = 1, int r = n) {
    if (l == r) seg[p] = a[l];
    else {
        int m = (l + r) >> 1;
        build(2 * p, l, m);
        build(2 * p + 1, m + 1, r);
        seg[p] = seg[2 * p] + seg[2 * p + 1];
    }
}
int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build();
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            ll x;
            cin >> x;
            update(l, r, x);
        } else cout << query(l, r) << endl;
    }
}