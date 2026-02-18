#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    auto id = [](pair<int, int> p) {
        return p.first * 5050 + p.second;
    };
    int n; cin >> n;
    int a, b, c, d; cin >> a >> b >> c >> d;
    int prv = 0;
    auto g = vector(6000000, vector<int>());
    auto add_edge = [&](pair<int, int> a, pair<int, int> b, bool undir) {
        g[id(a)].push_back(id(b));
        if (undir) g[id(b)].push_back(id(a));
    };
    for (int i = 1; i <= n; i++) {
        int l; cin >> l;
        if (i > 1) for (int j = 1; j <= prv + 1; j++) {
            add_edge({i - 1, j}, {i, min(j, l + 1)}, false);
        }
        for (int j = 1; j <= l + 1; j++) {
            if (i > 1) add_edge({i, j}, {i - 1, min(prv + 1, j)}, false);
            if (j > 1) add_edge({i, j - 1}, {i, j}, true);
        }
        if (i > 1) add_edge({i, 1}, {i - 1, prv + 1}, true);
        prv = l;
    }
    int st = id({a, b}), tgt = id({c, d});
    queue<int> q;
    q.push(st);
    const int inf = 1e15;
    vector<int> dist(6000000, inf);
    dist[st] = 0;
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v: g[u]) if (dist[v] == inf) {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    cout << dist[tgt] << endl;
}
