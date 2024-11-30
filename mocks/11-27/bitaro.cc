#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 1;
vector<int> g[N];
int d[N], l[N];

int main() {
    int n, m, q; cin >> n >> m >> q;
    while (m--) {
        int u, v; cin >> u >> v;
        g[v].push_back(u);
        ++d[u];
    }
    for (int i = n; i > 0; i--) {
        for (int j : g[i]) if (!--d[j]) l[j] = l[i] + 1;
    }
    while (q--) {
        int x, sz; cin >> x >> sz;
        vector<int> v(sz); for (int &x : v) cin >> x;
    }
}
