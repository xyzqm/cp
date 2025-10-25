#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int32_t main() {
    int n; cin >> n;
    vector<int> trie(1 << (n + 1)), rw(n);
    int inv = 0;
    auto add = [&](int x) {
        // cout << x << ": ";
        for (int k = n, cur = 2; k --> 0; cur <<= 1) {
            ++trie[cur ^= (x >> k & 1)];
            // cout << cur << " ";
            if (!(cur & 1)) {
                inv += trie[cur ^ 1];
                rw[k] -= trie[cur ^ 1];
            }
            else rw[k] += trie[cur ^ 1];
        }
        // cout << endl;
        // cout << x << " " << cur << endl;
    };

    for (int i = 0; i < (1 << n); i++) {
        int x; cin >> x;
        add(x);
    }

    // println("{}", rw);
    int ans = inv;
    for (int k = 0; k < n; k++) inv += min(rw[k], (int)0);
    cout << min(ans, inv + 1) << endl;
}
