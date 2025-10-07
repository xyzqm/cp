// https://codeforces.com/contest/505/problem/D
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<int> deg(n + 1);
    vector<vector<int>> g(n + 1), u_g(n + 1);
    while (m--) {
        int u, v; cin >> u >> v;
        ++deg[v];
        g[u].push_back(v);
        u_g[u].push_back(v);
        u_g[v].push_back(u);
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) if (!deg[i]) q.push(i);
    vector<int> mark(n + 1, 0);
    while (q.size()) {
        int x = q.front(); q.pop();
        mark[x] = 1;
        for (int y : g[x]) if (!--deg[y]) q.push(y);
    }
    auto dfs = [&](this auto dfs, int x) -> void {
        mark[x] = 2;
        for (int y : u_g[x]) if (mark[y] != 2) dfs(y);
    };
    int ans = n;
    for (int i = 1; i <= n; i++) if (!mark[i]) dfs(i);
    for (int i = 1; i <= n; i++) if (mark[i] == 1) ans--, dfs(i);
    cout << ans << endl;
}
