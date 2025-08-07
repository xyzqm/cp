// https://codeforces.com/contest/1893/problem/D
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int ac() {
    int n, m; cin >> n >> m;
    vector<int> frq(n + 1);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        ++frq[x];
    }
    set<array<int, 2>, greater<>> s;
    for (int i = 1; i <= n; i++) if (frq[i]) s.insert({frq[i], i});
    auto shelves = vector(m, vector<int>());
    for (int i = 0; i < m; i++) {
        int sz; cin >> sz;
        shelves[i].resize(sz);
    }
    vector<int> d(m);
    for (int &x : d) cin >> x;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < shelves[i].size(); j += d[i]) {
            int r = min((int)shelves[i].size(), j + d[i]);
            vector<array<int, 2>> tmp;
            for (int k = j; k < r; k++) {
                if (!s.size()) return -1;
                auto it = s.begin();
                shelves[i][k] = (*it)[1];
                tmp.push_back({(*it)[0] - 1, (*it)[1]});
                s.erase(it);
            }
            for (auto v : tmp) if (v[0]) s.insert(v);
        }
    }
    for (auto &shelf : shelves) {
        ranges::copy(shelf, ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    return 0;
}

int32_t main() {
    int t; cin >> t;
    while (t--) if (ac() < 0) cout << -1 << endl;
}
