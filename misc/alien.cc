#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 2e5 + 1;
const int inf = 1e18;

struct E { int w, v; };
vector<E> g[N];
int n, m, v[N], w[N], d[N], id[N], c[N], p[N];

vector<int> ac() {
    // reset and initialize varialbes
    cin >> n >> m;
    for (int i = 1; i <= n; i++) g[i].clear();
    fill(id, id + n + 1, -1);
    fill(v, v + n + 1, 0);
    fill(d, d + n + 1, inf);
    fill(w, w + n + 1, 0);
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        g[v].push_back({w, u});
    }
    // input sightings
    int q; cin >> q;
    for (int i = q; i --> 0; ) {
        cin >> c[i] >> p[i];
        if (id[p[i]] > i + 1) return {-1}; // all sightings of the same planet must be consecutive
        id[p[i]] = i;
    }
    // run djikstra
    using T = pair<int, int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({d[1] = 0, 1});
    int l = 0, r = inf;
    vector<int> s;
    while (pq.size()) {
        auto [d, x] = pq.top(); pq.pop();
        if (d != ::d[x]) continue;
        if (id[x] > -1) assert(v[x] <= id[x]);
        if (v[x] < id[x]) return {-1};
        int lt = inf, rt = -inf;
        for (; v[x] < q && p[v[x]] == x; v[x]++) {
            lt = min(lt, c[v[x]]);
            rt = max(rt, c[v[x]]);
        }
        if (id[x] > -1) {
            l = max(l, rt + d - w[x]);
            r = min(r, lt + d);
        }
        if (v[x] == q && d > l && d <= r) s.push_back(x);
        for (auto [w, y] : g[x]) {
            if (d + w < ::d[y]) {
                v[y] = v[x], ::w[y] = w;
                pq.push({::d[y] = d + w, y});
            }
            if (d + w == ::d[y]) {
                if (v[x] > v[y]) v[y] = v[x], ::w[y] = w;
                if (v[x] == v[y]) ::w[y] = max(::w[y], w);
            }
        }
    }
    sort(s.begin(), s.end());
    return s.size() ? s : vector<int>{-1};
}

int32_t main() {
    int t; cin >> t;
    while (t--) {
        for (int x : ac()) cout << x << " ";
        cout << endl;
    }
}
