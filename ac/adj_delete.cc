// https://atcoder.jp/contests/arc196/tasks/arc196_a
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int N = 3e5 + 1;

int n, a[N], pre[N], suf[N];

int32_t main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    auto comp = [&](int *arr, int l, int r, int st) {
        multiset<int> sb, pl;
        int dif = st / abs(st);
        for (int i = l, tot = 0; i != r; i += st) {
            sb.insert(a[i]);
            sb.insert(a[i + dif]);
            tot -= a[i] + a[i + dif];
            pl.insert(*sb.rbegin());
            tot += 2 * *sb.rbegin();
            sb.erase(--sb.end());
            while (*sb.rbegin() > *pl.begin()) {
                int u = *sb.rbegin(), v = *pl.begin();
                sb.erase(--sb.end());
                pl.erase(pl.begin());
                pl.insert(u);
                sb.insert(v);
                tot += 2 * (u - v);
            }
            arr[i + st] = tot;
        }
    };
    comp(pre, 0, 2 * (n / 2), 2);
    if (n % 2 == 0) cout << pre[n] << endl;
    else {
        comp(suf, n - 1, 0, -2);
        int x = 0;
        for (int i = 0; i < n; i += 2) x = max(x, pre[i] + suf[i]);
        cout << x << endl;
    }
}
