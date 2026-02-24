#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int m;

void ac() {
    int n; cin >> n;
    vector<int> v(n);
    for (int &x : v) cin >> x;
    int tot = 0;
    auto operate = [&](int l, int r, int k) {
        tot += k;
        for (int i = max((int)0, l); i < min(n, r); i++) v[i] -= k;
    };
    vector<array<int, 2>> ops, ops_r;
    for (int i = 0; i < n; i++) {
        if (i + 1 < n && v[i] > v[i + 1]) {
            ops_r.push_back({i, v[i] - v[i + 1]});
            operate(i - 1, i + 1, v[i] - v[i + 1]);
        }
        if (i && v[i - 1] > 0) {
            ops.push_back({i, v[i - 1]});
            operate(i - 1, i + 2, v[i - 1]);
        }
    }
    if (v.back()) ops.push_back({n - 1, v.back()});
    ops.insert(ops.end(), ops_r.rbegin(), ops_r.rend());
    DBG(ops);
    cout << tot + v.back() << "\n";
    if (m) {
        cout << ops.size() << "\n";
        for (auto &[idx, v] : ops) {
            cout << idx + 1 << " " << v << "\n";
        }
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t >> m;
    // if (m > 1) {
    //     cout << "10\n1\n1 10\n12\n3\n2 1\n3 6\n1 5\n";
    // }
    while (t--) ac();
}
