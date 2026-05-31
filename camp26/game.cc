#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define all(v) v.begin(), v.end()

struct basis : vector<int> {
    void add(int x) {
        for (auto it = rbegin(); it != rend(); it++) x = min(x, x ^ *it);
        if (x) {
            int i = 0;
            while (i < size() && at(i) < x) ++i;
            insert(begin() + i, x);
        }
    }
};

void ac() {
    int n, m; cin >> n >> m;
    int val = 0;
    basis a, b;
    while (n--) {
        int x, y; cin >> x >> y;
        val ^= x;
        a.add(x ^ y);
    }
    while (m--) {
        int x, y; cin >> x >> y;
        val ^= x;
        b.add(x ^ y);
    }
    while (a.size() && b.size()) {
        if (__builtin_clzll(a.back()) < __builtin_clzll(b.back())) {
            val = max(val, val ^ a.back());
            a.pop_back();
        }
        else if (__builtin_clzll(b.back()) < __builtin_clzll(a.back())) {
            val = min(val, val ^ b.back());
            b.pop_back();
        }
        else { // same
            val = min(val, val ^ b.back());
            int nw = a.back() ^ b.back();
            a.pop_back();
            b.pop_back();
            a.add(nw);
        }
    }
    sort(all(a), greater<int>());
    for (int x : a) val = max(val, val ^ x);
    sort(all(b), greater<int>());
    for (int x : b) val = min(val, val ^ x);
    cout << val << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
