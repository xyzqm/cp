// https://qoj.ac/submission/2167921
#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

#define int int64_t

const int N = 1e5 + 1;

vector<vector<int>> g;
vector<int> leaf_dist, sz, ans, dist;
vector<bool> removed;

int dummy;

// shifted vector
struct shift : vector<int> {
    int base = 0;
    shift(int n, int b) : vector(n, 0), base(b) {}
    int& operator[](int i) {
        return at(i - base);
    }
    int read(int i) const {
        return i < base ? 0 : at(min(i - base, (int)size() - 1));
    }
    int mx() { return base + size(); }
};

int get_sz(int x, int p, int &base) {
    sz[x] = 1;
    dist[x] = dist[p] + 1;
    base = min(base, leaf_dist[x] - dist[x]);
    for (int y : g[x]) if (y != p && !removed[y]) sz[x] += get_sz(y, x, base);
    return sz[x];
}

void fill(int x, int p, shift &v, vector<int> &u) {
    u.push_back(x);
    v[leaf_dist[x] - dist[x]] += 2 - g[x].size();
    for (int y : g[x]) if (y != p && !removed[y]) fill(y, x, v, u);
}

void decompose(int x, int p, int n) {
    for (int y : g[x]) if (y != p && !removed[y] && sz[y] > n / 2) return decompose(y, x, n);
    // this is the centroid
    vector<shift> cs; // vals for children
    vector<vector<int>> us; // children in each subtree
    dist[x] = 0;
    for (int y : g[x]) if (!removed[y]) {
        cs.push_back(shift(2 * sz[y] + 1, N));
        get_sz(y, x, cs.back().base);
        us.emplace_back();
        fill(y, x, cs.back(), us.back());
        partial_sum(all(cs.back()), cs.back().begin());
    }

    shift ov(2 * n + 1, N); // overall value
    get_sz(x, 0, ov.base);
    us.emplace_back();
    fill(x, 0, ov, us.back());
    partial_sum(all(ov), ov.begin());
    ans[x] += ov.read(0); // account for paths starting from centroid first
    for (int sb = 0; sb < cs.size(); sb++) { // enumerate subtree of starting node
        for (int u : us[sb]) ans[u] += ov.read(dist[u]) - cs[sb].read(dist[u]);
    }
    removed[x] = true;
    for (int y : g[x]) if (!removed[y]) decompose(y, 0, get_sz(y, 0, dummy));
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    g.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    leaf_dist.assign(n + 1, n + 1);
    queue<int> q;
    for (int i = 1; i <= n; i++) if (g[i].size() == 1) q.push(i), leaf_dist[i] = 0;
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) if (leaf_dist[u] + 1 < leaf_dist[v]) {
            leaf_dist[v] = leaf_dist[u] + 1;
            q.push(v);
        }
    }
    removed.assign(n + 1, false);
    sz.resize(n + 1);
    ans.assign(n + 1, 0);
    dist.resize(n + 1);
    dist[0] = -1;
    decompose(1, 0, get_sz(1, 0, dummy));
    for (int i = 1; i <= n; i++) {
        cout << array{ans[i], (int)1}[g[i].size() == 1] << "\n";
    }
}
