// http://www.usaco.org/index.php?page=viewproblem2&cpid=719

#include <bits/stdc++.h>
using namespace std;
const int N = 5e4;
using ll = long long;
int n, l[N + 1];
int sum[8 * N]; // 4 * (2 * N)
int _query(int p, int l, int r, int i, int j) {
    if (r < i || l > j) return 0;
    if (i <= l && r <= j) return sum[p];
    int m = (l + r) / 2;
    return _query(2 * p, l, m, i, j) + _query(2 * p + 1, m + 1, r, i, j);
}
int query(int l, int r) {
    return _query(1, 1, 2 * n, l, r);
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
    return _update(1, 1, 2 * n, i, x);
}

int main() {
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);
    cin >> n;
    ll ans = 0;
    for (int i = 1; i <= 2 * n; i++) {
        int x; cin >> x;
        if (!l[x]) {
            l[x] = i;
            update(l[x], 1);
        } else {
            ans += query(l[x], i) - 1;
            update(l[x], -1);
        }
    }
    cout << ans << endl;
}