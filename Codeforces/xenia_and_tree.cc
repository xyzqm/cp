#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#define UPD(a, b) a = min(a, b)
using namespace std;
const int N = 1e5;
const int K = 18;
const int B = 300;
int n, q, i1 = -1, i2 = -1, d[N + 1], dist[N + 1], id[N + 1], pos[N + 1], a[2 * N], stl[2 * N][K], str[2 * N][K];
vector<int> g[N + 1];
void dfs(int x, int p) {
    if (id[x] < 0) id[x] = ++i1;
    d[id[x]] = dist[x];
    if (p && g[x].size() == 1) {
        a[++i2] = id[x];
        if (pos[x] < 0) pos[x] = i2;
    }
    for (int y : g[x]) {
        if (y == p) continue;
        a[++i2] = id[x];
        if (pos[x] < 0) pos[x] = i2;
        dist[y] = dist[x] + 1;
        dfs(y, x);
    }
}
int dst(int u, int v) {
    int l = pos[u], r = pos[v];
    if (l > r) swap(l, r);
    int k = log2(r - l + 1);
    int lca = min(stl[l][k], str[r][k]);
    return d[id[u]] + d[id[v]] - 2 * d[lca];
}
int main() {
    cin >> n >> q;
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    fill(id, id + N + 1, -1);
    fill(pos, pos + N + 1, -1);
    fill(dist, dist + N + 1, INT_MAX);
    dfs(1, dist[1] = 0);
    for (int i = 0; i <= i2; ++i) stl[i][0] = str[i][0] = a[i];
    for (int k = 1; k < K; ++k) {
        for (int i = 0; i <= i2; ++i) {
            stl[i][k] = stl[i][k - 1];
            if (int j = i + (1 << (k - 1)); j <= i2) UPD(stl[i][k], stl[j][k - 1]);
            str[i][k] = str[i][k - 1];
            if (int j = i - (1 << (k - 1)); j >= 0) UPD(str[i][k], str[j][k - 1]);
        }
    }
    vector<int> buf;
    while (q--) {
        int t, v;
        cin >> t >> v;
        if (t == 1) {
            buf.push_back(v);
            if (buf.size() >= B) {
                queue<int> bfs;
                for (int j : buf) {
                    dist[j] = 0;
                    bfs.push(j);
                }
                while (bfs.size()) {
                    int j = bfs.front();
                    bfs.pop();
                    for (int k : g[j]) {
                        if (dist[j] + 1 < dist[k]) {
                            dist[k] = dist[j] + 1;
                            bfs.push(k);
                        }
                    }
                }
                buf.clear();
            }
        } else {
            int ans = dist[v];
            for (int j : buf) ans = min(ans, dst(v, j));
            cout << ans << endl;
        }
    }
}