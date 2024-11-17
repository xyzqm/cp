#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define L(x) ((x) << 1)
#define R(x) (((x) << 1) + 1)
using ll = long long;
const int N = 1e5;
const ll inf = 1e18;
vector<pair<int, ll>> g[9 * N];
ll dist[9 * N];
int n, q, s;
// to -> whether edges are going to x or away from it
void update(int i, int j, int x, ll w, bool to, int p = 1, int l = 1, int r = n) {
    if (l > j || r < i) return;
    else if (i <= l && r <= j) {
        if (to) g[p + 5 * N].push_back({x, w});
        else g[x].push_back({p + N, w});
    } else {
        int m = (l + r) >> 1;
        update(i, j, x, w, to, 2 * p, l, m);
        update(i, j, x, w, to, 2 * p + 1, m + 1, r);
    }
}
void build(int p = 1, int l = 1, int r = n) {
    if (l == r) {
        g[p + N].push_back({l, 0});
        g[l].push_back({p + 5 * N, 0});
    } else {
        int m = (l + r) >> 1;
        // segtree 1 -> edges go to children
        g[p + N].push_back({L(p) + N, 0});
        g[p + N].push_back({R(p) + N, 0});
        // segtree 2 -> edges go to parent
        g[L(p) + 5 * N].push_back({p + 5 * N, 0});
        g[R(p) + 5 * N].push_back({p + 5 * N, 0});

        build(2 * p, l, m);
        build(2 * p + 1, m + 1, r);
    }
}
int main() {
    cin >> n >> q >> s;
    build();
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int v, u;
            ll w;
            cin >> v >> u >> w;
            g[v].push_back({u, w});
        } else {
            int v, l, r;
            ll w;
            cin >> v >> l >> r >> w;
            if (t == 2) update(l, r, v, w, false);
            else update(l, r, v, w, true);
        }
    }
    fill(dist, dist + 9 * N, inf);
    using T = pair<long long, int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({dist[s] = 0, s});
    while (pq.size()) {
        auto [d, x] = pq.top();
        pq.pop();
        if (d != dist[x]) continue;
        for (auto [y, w] : g[x]) if (d + w < dist[y]) pq.push({dist[y] = d + w, y});
    }
    for (int i = 1; i <= n; i++) cout << (dist[i] == inf ? -1 : dist[i]) << " ";
    cout << endl;
}