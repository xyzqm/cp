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
    auto g = vector(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    DBG(g);
    vector<vector<int>> chains;
    vector<int> idx(n + 1, -1);
    chains.push_back({1});
    idx[1] = 0;
    vector<int> cur = {1}, free;
    auto add_edge = [&](int u, int v) {
        if (idx[u] < 0) idx[u] = chains.size(), chains.push_back({u});
        if (v <= n) chains[idx[v] = idx[u]].push_back(v);
    };
    while (cur.size()) {
        DBG(cur);
        DBG(free);
        auto leaf = [&](int u) { return !g[u].size(); };
        ranges::copy_if(cur, back_inserter(free), leaf);
        erase_if(cur, leaf);

        for (int u : cur) for (int v : g[u]) erase(g[v], u); // erase paretns

        if (cur.size() > 1) { // we can pair off all nodes in cur
            for (int i = 0; i < cur.size(); i++) {
                add_edge(cur[i], g[cur[(i + 1) % cur.size()]][0]);
            }
        }
        vector<int> nx;
        for (int u : cur) for (int v : g[u]) {
            nx.push_back(v);
            if (free.size() && idx[v] < 0) {
                add_edge(free.back(), v);
                free.pop_back();
            }
        }
        if (cur.size() == 1) free.push_back(cur[0]);
        cur = nx;
    }
    for (int i = 1; i <= n; i++) add_edge(i, n + 1); // len-1 chains
    cout << chains.size() << "\n";
    for (auto &chain : chains) {
        cout << chain.size() << " ";
        for (int &u : chain) cout << u << " ";
        cout << "\n";
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
