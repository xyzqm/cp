#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

vector<int> query(int k) {
    cout << "? " << k << endl;
    int n; cin >> n;
    if (n == -1) exit(0);
    vector<int> v(n);
    for (int &x : v) cin >> x;
    return v;
}

void ac() {
    int n; cin >> n;
    vector<int> s(n + 1, 1);
    vector<int> cur = {1};
    int kk = 1;
    vector<array<int, 2>> g;
    while (cur.size()) {
        int dif = s[cur.back()];
        cur.pop_back();
        for (int x : cur) s[x] += dif;
        auto nx = query(kk += dif);
        if (nx.size() > 1) g.push_back({nx[nx.size() - 2], nx.back()});
        cur = nx;
    }
    cout << "! " << g.size() << endl;
    for (auto &[u, v] : g) cout << u << " " << v << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
