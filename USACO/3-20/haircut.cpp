// http://www.usaco.org/index.php?page=viewproblem2&cpid=1041

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int N = 1e5;
int n, a[N];
ll inv[N], ans[N];
vector<int> inds[N + 1];
int sum[4 * N];
int _query(int p, int l, int r, int i, int j) {
    if (r < i || l > j) return 0;
    if (i <= l && r <= j) return sum[p];
    int m = (l + r) / 2;
    return _query(2 * p, l, m, i, j) + _query(2 * p + 1, m + 1, r, i, j);
}
int query(int l, int r) {
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

int main() {
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        inds[a[i]].push_back(i);
    }
    ll res = 0;
    for (int i = n; i >= 0; i--) {
        for (int ind : inds[i]) {
            int invs = query(0, ind - 1);
            res += invs;
            inv[i] += invs;
        }
        for (int ind : inds[i]) update(ind, 1);
    }
    for (int i = n - 1; i >= 0; i--) ans[i] = res -= inv[i];
    for (int i = 0; i < n; i++) cout << ans[i] << endl;
}