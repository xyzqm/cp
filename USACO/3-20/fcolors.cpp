#include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("fcolor.in", "r", stdin);
    freopen("fcolor.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<set<int>> adj(n + 1);
    queue<int> par;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (adj[a].find(b) != adj[a].end()) continue;
        adj[a].insert(b);
        if (adj[a].size() == 2) par.push(a);
    }
    vector<set<int>> comp(n + 1);
    vector<int> rep(n + 1);
    for (int i = 1; i <= n; i++) {
        rep[i] = i;
        comp[i].insert(i);
    }
    int compc = 0;
    while (par.size()) {
        int x = par.front();
        par.pop();
        if (adj[x].size() < 2) continue;
        int r = rep[*adj[x].begin()];
        adj[x].erase(adj[x].begin());
        while (adj[x].size()) {
        int y = rep[*adj[x].begin()];
        adj[x].erase(adj[x].begin());
        if (r == y) continue;
        if (comp[r].size() < comp[y].size()) swap(r, y);
        for (int z : comp[y]) {
            rep[z] = r;
            comp[r].insert(z);
        }
        comp[y].clear();
        if (adj[r].size() < adj[y].size()) adj[r].swap(adj[y]);
        for (int z : adj[y]) adj[r].insert(z);
        adj[y].clear();
        }
        adj[x].insert(r);
        if (adj[r].size() > 1) par.push(r);
    }
    vector<int> mp(n + 1);
    int c = 0;
    for (int i = 1; i <= n; i++) {
        int x = rep[i];
        if (!mp[x]) mp[x] = ++c;
        cout << mp[x] << endl;
    }
}