#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int ac() {
    int n, k, sm = 0, mx = 0; cin >> n >> k;
    multiset<int> s;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        s.insert(x);
        sm += x;
        mx = max(mx, x);
    }
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = *s.rbegin();
        auto nh = s.extract(s.begin());
        ++nh.value();
        s.insert(move(nh));
    }
    for (int i = n; i > 0; i--) {
        if (sm <= mx * i && mx * i - sm <= k) return i;
        int ad = (i - sm % i) % i;
        if (ad <= k && res[ad] <= (sm + ad) / i) return i;
    }
    assert(false);
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << ac() << endl;
}
