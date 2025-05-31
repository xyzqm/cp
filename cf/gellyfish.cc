// https://codeforces.com/contest/2116/problem/D
#include <bits/stdc++.h>
using namespace std;

void ac() {
    int n, q; cin >> n >> q;
    vector<int> a(n + 1);
    vector<array<int, 2>> b(n + 1), g(n + 1);
    for (int i = 1; i <= n; i++) {
        b[i][1] = i;
        cin >> b[i][0];
    }
    sort(b.begin(), b.end(), greater<>());
    vector<int> idx(n + 1);
    iota(idx.begin(), idx.end(), 0);
    while (q--) {
        int x, y, z; cin >> x >> y >> z;
        g.push_back({idx[x], idx[y]});
        idx[z] = a.size();
        a.push_back(0);
    }
    function<bool(int, int)> dfs = [&](int x, int v) {
        if (!x || a[x] > v) return false;
        else if (a[x] == v) return true;
        bool w = !g[x][0] && !g[x][1];
        for (int t : {0, 1}) w = dfs(g[x][t], v) || w;
        if (w) a[x] = v;
        return w;
    };
    for (auto [v, i] : b) if (v) {
        if (!dfs(idx[i], v)) {
            cout << -1 << endl;
            return;
        }
    }
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
