// https://judge.yosupo.jp/problem/point_add_range_sum

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5;
int n, a[N];
ll sum[4 * N];
ll _query(int p, int l, int r, int i, int j) {
    if (r < i || l > j) return 0;
    if (i <= l && r <= j) return sum[p];
    int m = (l + r) / 2;
    return _query(2 * p, l, m, i, j) + _query(2 * p + 1, m + 1, r, i, j);
}
ll query(int l, int r) {
    return _query(1, 0, n - 1, l, r);
}
void _update(int p, int l, int r, int i, int x) {
    if (l == r) sum[p] += x;
    else {
        int m = (l + r) / 2;
        if (i <= m) _update(2 * p, l, m, i, x);
        else _update(2 * p + 1, m + 1, r, i, x);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
}
void update(int i, int x) {
    return _update(1, 0, n - 1, i, x);
}
void _build(int p, int l, int r) {
    if (l == r) sum[p] = a[l];
    else {
        int m = (l + r) / 2;
        _build(2 * p, l, m); 
        _build(2 * p + 1, m + 1, r);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
}
void build() {
    _build(1, 0, n - 1);
}
int main() {
    int q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    build();
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        if (x == 0) update(y, z);
        else cout << query(y, z - 1) << endl;
    }
}