// https://www.spoj.com/problems/KQUERY/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int N = 3e4, Q = 2e5;
int n, q, a[N + 1], ans[Q];
struct Query {
    int i, j, k, ind;
} queries[Q];
ll sum[4 * N];
ll _query(int p, int l, int r, int i, int j) {
    if (r < i || l > j) return 0;
    if (i <= l && r <= j) return sum[p];
    int m = (l + r) / 2;
    return _query(2 * p, l, m, i, j) + _query(2 * p + 1, m + 1, r, i, j);
}
ll query(int l, int r) {
    return _query(1, 1, n, l, r);
}
void _update(int p, int l, int r, int i, int x) {
    if (l == r) sum[p] = x;
    else {
        int m = (l + r) / 2;
        if (i <= m) _update(2 * p, l, m, i, x);
        else _update(2 * p + 1, m + 1, r, i, x);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
}
void update(int i, int x) {
    return _update(1, 1, n, i, x);
}
int main() {
    cin >> n;
    set<pii, greater<pii>> vals;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        vals.insert({a[i], i});
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> queries[i].i >> queries[i].j >> queries[i].k;
        queries[i].ind = i;
    }
    sort(queries, queries + q, [](Query& a, Query& b) { return a.k > b.k; });
    int qi = 0; // index of current query to be processed
    for (pii p : vals) {
        while (qi < q && queries[qi].k >= p.first) {
            Query cur = queries[qi];
            ans[cur.ind] = query(cur.i, cur.j);
            qi++;
        }
        update(p.second, 1);
    }
    while (qi < q) {
        Query cur = queries[qi];
        ans[cur.ind] = query(cur.i, cur.j);
        qi++;
    }
    for (int i = 0; i < q; i++) cout << ans[i] << endl;
}