#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 1;

int n, m, h[N];
unsigned sd;
int rd() {
    return (sd ^= sd << 13, sd ^= sd >> 17, sd ^= sd << 5) % n + 1;
}

#define int int64_t
vector<array<int, 2>> qs[N];

const int M = 998244353;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> sd;
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 1; i <= m; i++) {
        int l = rd(), r = rd();
        if (l > r) swap(l, r);
        qs[l].push_back({r, i});
    }
    vector<int> stk;
    int ans = 0;
    for (int i = n; i > 0; i--) {
        while (stk.size() && h[i] >= h[stk.back()]) stk.pop_back();
        stk.push_back(i);
        for (auto &[r, idx] : qs[i]) {
            auto it = lower_bound(stk.begin(), stk.end(), r, greater<int>());
            ans = (ans + (stk.end() - it) * idx) % M;
        }
    }
    cout << ans << endl;
}
