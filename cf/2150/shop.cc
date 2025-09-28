// https://codeforces.com/contest/2150/problem/C
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void ac() {
    int n; cin >> n;
    vector<int> v(n), a(n), b(n), idx(n + 1);
    for (auto x : {ref(v), ref(a), ref(b)}) for (int &y : x.get()) cin >> y;
    v.insert(v.begin(), 0);
    for (int i = 0; i < n; i++) idx[b[i]] = i;
    set<pair<int, int>> unused;
    int ans = 0;
    for (int x : a) {
        while (v[x] >= 0) {
            unused.erase({idx[x], x});
            auto it = unused.lower_bound({idx[x], 0});
            if (it == unused.end()) break;
            v[it->second] += v[x];
            x = it->second;
        }
        if (v[x] >= 0) ans += v[x];
        else unused.insert({idx[x], x});
    }
    cout << ans << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
