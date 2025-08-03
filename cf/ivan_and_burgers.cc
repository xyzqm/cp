// https://codeforces.com/contest/1100/problem/F
#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 1;
const int K = 20;

int n, q, a[N], ans[N], b[K];
vector<array<int, 2>> qs[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        qs[l].push_back({r, i});
    }
    for (int i = n; i > 0; i--) {
        int idx = i;
        for (int k = K; k --> 0; ) if (a[idx] >> k & 1) {
            if (!b[k]) {
                b[k] = idx;
                break;
            }
            if (idx < b[k]) swap(idx, b[k]);
            a[idx] ^= a[b[k]];
        }
        for (auto [j, qi] : qs[i]) for (int k = K; k --> 0; ) if (b[k] && b[k] <= j) {
            ans[qi] = max(ans[qi], ans[qi] ^ a[b[k]]);
        }
    }
    for (int i = 0; i < q; i++) cout << ans[i] << endl;
}
