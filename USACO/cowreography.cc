#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int32_t main() {
    int n, k; cin >> n >> k;
    string a, b; cin >> a >> b;
    int ans = 0;
    multiset<int> opts;
    for (int i = 0; i < n; i++) {
        if (!opts.size() && a[i] == '0' && b[i] == '1') a.swap(b);
        if (a[i] == '1') opts.insert(i % k), ans -= i;
        if (b[i] == '1') {
            assert(opts.size());
            auto it = opts.lower_bound(i % k);
            if (it == opts.end()) it = opts.begin();
            int dif = *it - (i % k);
            if (dif < 0) dif += k;
            ans += i + dif;
            opts.erase(it);
        }
    }
    assert(ans % k == 0);
    cout << ans / k << endl;
}
