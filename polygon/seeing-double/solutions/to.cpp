#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int ac() {
    // int n; cin >> n;
    string s; cin >> s;
    // auto pos = vector(26, vector<int>());
    vector<vector<int>> pos(26);
    for (int i = 0; i < s.size(); i++) pos[s[i] - 'a'].push_back(i);
    vector<array<int, 2>> ps;
    for (auto &v : pos) {
        if (v.size() % 2) return -1;
        for (int i = 0; i < v.size() / 2; i++) ps.push_back({v[i], v[i + v.size() / 2]});
    }
    DBG(ps);
    int ans = 0;
    for (int i = 0; i < ps.size(); i++) {
        for (int j = i + 1; j < ps.size(); j++) {
            auto [a, b] = ps[i];
            auto [c, d] = ps[j];
            if (a > c) swap(a, c), swap(b, d);
            if (b < c || b > d) ++ans;
        }
    }
    return ans;
}

int32_t main() {
    // cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) cout << ac() << "\n";
}
