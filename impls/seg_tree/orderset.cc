// https://www.spoj.com/problems/ORDERSET/en/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5;
char op[N];
int n, q, x[N];
ll sum[4 * N];
map<int, int> mp, rmp;
ll _query1(int p, int l, int r, int k) {
    if (l == r) return rmp[l];
    int m = (l + r) / 2;
    if (k <= sum[2 * p]) return _query1(2 * p, l, m, k);
    else return _query1(2 * p + 1, m + 1, r, k - sum[2 * p]);
}
ll query1(int k) { return _query1(1, 0, n - 1, k); }
ll _query2(int p, int l, int r, int qr) {
    if (l > qr) return 0;
    if (r <= qr) return sum[p];
    int m = (l + r) / 2;
    return _query2(2 * p, l, m, qr) + _query2(2 * p + 1, m + 1, r, qr);
}
ll query2(int x) { return _query2(1, 0, n - 1, x - 1); }
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
    return _update(1, 0, n - 1, i, x);
}
int main() {
    cin >> q;
    set<int> nums;
    for (int i = 0; i < q; i++) {
        cin >> op[i] >> x[i];
        if (op[i] == 'I' || op[i] == 'C' || op[i] == 'D') nums.insert(x[i]);
    }
    n = nums.size();
    int cnt = 0;
    for (int x : nums) {
        mp[x] = cnt; rmp[cnt] = x;
        cnt++;
    }
    for (int i = 0; i < q; i++) {
        if (op[i] != 'K') x[i] = mp[x[i]];
        if (op[i] == 'I') {
            update(x[i], 1);
        } else if (op[i] == 'D') {
            update(x[i], 0);
        } else if (op[i] == 'K') {
            if (x[i] > sum[1]) cout << "invalid" << endl;
            else cout << query1(x[i]) << endl;
        } else {
            cout << query2(x[i]) << endl;
        }
    }
}