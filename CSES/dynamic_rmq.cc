#include <iostream>
#define COMB(a, b) min(a, b)
using namespace std;
using ll = long long;
const int N = 2e5 + 1;
int n, q, a[N];
ll seg[4 * N];
ll query(int i, int j, int p = 1, int l = 1, int r = n) {
    if (r < i || l > j) return 1e18;
    if (i <= l && r <= j) return seg[p];
    int m = (l + r) / 2;
    return COMB(query(i, j, 2 * p, l, m), query(i, j, 2 * p + 1, m + 1, r));
}
void upd(int i, int x, int p = 1, int l = 1, int r = n) {
    if (l == r) seg[p] = x;
    else {
        int m = (l + r) / 2;
        if (i <= m) upd(i, x, 2 * p, l, m);
        else upd(i, x, 2 * p + 1, m + 1, r);
        seg[p] = COMB(seg[2 * p], seg[2 * p + 1]);
    }
}
void build(int p = 1, int l = 1, int r = n) {
    if (l == r) seg[p] = a[l];
    else {
        int m = (l + r) / 2;
        build(2 * p, l, m); 
        build(2 * p + 1, m + 1, r);
        seg[p] = COMB(seg[2 * p], seg[2 * p + 1]);
    }
}
int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build();
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        if (x == 1) upd(y, z);
        else cout << query(y, z) << endl;
    }
}