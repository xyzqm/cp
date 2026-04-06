#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n; cin >> n;
    string a, b; cin >> a >> b;
    auto g = vector(n + 1, vector<array<int, 2>>());
    int m; cin >> m;
    vector<int> self_loop(n);
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[--u].push_back({--v, i});
        if (u == v) self_loop[u] = i;
    }
    auto mx_ones = [&](string &s) {
        vector<int> ops;
        queue<int> q;
        for (int i = 0; i < n; i++) if (s[i] == '1') q.push(i);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (auto &[v, e] : g[u]) if (s[v] == '0') {
                s[v] = '1';
                ops.push_back(e);
                q.push(v);
            }
        }
        return ops;
    };
    auto pref = mx_ones(a);
    DBG(pref);
    DBG(a);
    vector<int> suf;
    for (int i = 0; i < n; i++) if (self_loop[i] && a[i] == '1' && b[i] == '0') {
        b[i] = '1';
        suf.push_back(self_loop[i]);
    }
    suf.append_range(mx_ones(b));
    DBG(b);
    ranges::reverse(suf);
    pref.append_range(suf);
    if (a != b) cout << "-1\n";
    else {
        cout << pref.size() << "\n";
        for (int e : pref) cout << e << " ";
        cout << "\n";
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
