#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void ac() {
    int n; cin >> n;
    auto rngs = vector(n, array<int, 2>());
    int sm = 0;
    vector<int> opts;
    for (auto &[l, r] : rngs) {
        cin >> l >> r;
        sm += r - 2 * l;
        opts.push_back(r + l);
    }
    // println("{}", opts);
    ranges::sort(opts, greater());
    int dif = 0;
    if (n & 1) for (auto &[l, r] : rngs) {
        int cur = l;
        if (n == 1 || r + l >= opts[n / 2 - 1]) cur = opts[n / 2] - r;
        dif = max(dif, cur);
    }
    cout << sm + dif + accumulate(opts.begin(), opts.begin() + n / 2, 0LL) << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
