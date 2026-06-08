#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

// need to maintain:
// # of undetermined paths
// sum of already determined paths
// sum of already determined edges
// sum of each edge * (the # of undetermined paths its a part of)
void ac() {
    int n, w; cin >> n >> w;
    vector<int> p(n + 1);
    auto g = vector(n + 1, vector<int>());
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        g[p[i]].push_back(i);
    }
    auto paths = vector(n + 1, vector<int>());
    auto len = vector(n + 1, 0);
    auto mem = vector(n + 1, vector<int>());
    int lst = 1;
    [&](this auto dfs, int x, int p) -> void {
        for (int y : g[x]) if (y != p) {
            paths[lst].push_back(y);
            mem[y].push_back(lst);
            lst = y;
            dfs(y, x);
            paths[lst].push_back(y);
            mem[y].push_back(lst);
        }    
    }(1, 0);
    for (int i = 1; i <= n; i++) len[i] = paths[i].size();
    int q = n - 1, un = n, det = 0, det_edges = 0, edgeXun = 0;
    vector<int> t(n + 1);
    // DBG(paths); DBG(len);
    while (q--) {
        int e, v; cin >> e >> v;
        det_edges += (t[e] = v);
        for (int p : mem[e]) if (len[p]) edgeXun += v;
        for (int p : mem[e]) if (!--len[p]) { // path fully determined
            --un;
            for (int ee : paths[p]) {
                det += t[ee];
                edgeXun -= t[ee];
            }
        }
        // DBG(det);
        // DBG(un);
        cout << det + un * (w - det_edges) + edgeXun << " "; 
    }
    cout << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}