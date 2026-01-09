#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

/*
Process from shallowest to deepest level. For nodes on layer l,
first try to pair with nodes from layer l - 2. Then, try layer l - 1.

Implementation details:
Store a deque for each layer. When pairing with l - 2, just pop.
When pairing with l - 1, just try both front and back.
*/

void ac() {
    int n; cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<deque<int>> layers(n);
    vector<int> fa(n + 1);
    auto dfs = [&](this auto dfs, int x, int p, int d) -> void {
        layers[d].push_back(x);
        fa[x] = p;
        for (int y : g[x]) if (y != p) {
           dfs(y, x, d + 1);
        }
    };
    dfs(1, 0, 0);
    DBG(layers);
    DBG(fa);
    vector<vector<int>> chains;
    vector<int> idx(n + 1);
    int lst = 0;
    for (int i = 0; i < n; i++) {
        DBG(i);
        DBG(layers);
        for (int x : layers[i]) {
            int prv = 0;
            if (lst < i && layers[lst].size()) {
                auto &l = layers[lst];
                if (l.back() != fa[x]) prv = l.back(), l.pop_back();
                else if (l.front() != fa[x]) prv = l.front(), l.pop_front();
            }
            while (lst < i && !layers[lst].size()) lst++;
            if (!prv) {
                idx[x] = chains.size();
                chains.push_back({x});
            }
            else chains[idx[x] = idx[prv]].push_back(x);
        }
    }
    DBG(chains);
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
