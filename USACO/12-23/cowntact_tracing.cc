// https://usaco.org/index.php?page=viewproblem2&cpid=1356
#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;

const int N = 1e5 + 1;
int n, d[N], p[N], sz[N], rem[N], cp[N], cln[N], src[N];
string s;
vector<int> g[N];

// util for log
constexpr int lg(int x) {
  return 31 - __builtin_clz(x);
}

// o(1) lca with rmq
const int K = 20;
int t = 0, tt[N], et[2 * N], st[2 * N][K]{};

int mind(int i, int j) { // min by depth
    return d[i] < d[j] ? i : j;
}

void build() {
	for (int i = 0; i < 2 * N; i++) st[i][0] = et[i];
	for (int k = 1; k < K; k++) for (int i = 0; i < 2 * N; i++) {
		st[i][k] = st[i][k - 1];
		if (int j = i + (1 << (k - 1)); j < 2 * N) st[i][k] = mind(st[i][k], st[j][k - 1]);
	}
}

int lca(int u, int v) { // lca of u and v
    u = tt[u], v = tt[v];
    if (u > v) swap(u, v);
    int k = lg(++v - u);
    return mind(st[u][k], st[v - (1 << k)][k]);
}

int dist(int u, int v) {
    return d[u] + d[v] - 2 * d[lca(u, v)];
}

// centroid decomposition
int dfs(int x, bool init = 0, int p = 0) {
    sz[x] = 0;
    if (init) d[x] = d[p] + 1, ::p[x] = p;
    for (int y : g[x]) {
        if (init) et[tt[x] = t++] = x;
        if (y != p && !rem[y]) sz[x] += dfs(y, init, x);
    }
    return ++sz[x];
}

int decompose(int x, int n, int p = 0) {
    for (int y : g[x]) if (y != p && !rem[y] && sz[y] > n / 2) return decompose(y, n, x);
    // still here -> x is a centroid
    rem[x] = 1;
    for (int y : g[x]) if (!rem[y]) cp[decompose(y, dfs(y))] = x;
    return x;
}

vector<int> o;
vector<int> v[N];
int nx[N];
vector<int>::iterator it[N];
int ac() {
    int k; cin >> k;
    fill(nx, nx + N, 0);
    for (int i = 1; i <= n; i++) it[i] = v[i].begin();
    for (int x : o) if (s[x] == '1' && cln[x] > k) {
        for (int y = x; y; y = cp[y]) {
            while (it[y] != v[y].end() && dist(x, y) + dist(y, *it[y]) <= k) {
                if (!nx[*it[y]]) nx[*it[y]] = x;
                ++it[y];
            }
        }
    }
    fill(src, src + N, inf);
    int r = 0;
    for (auto it = o.rbegin(); it != o.rend(); it++) if (s[*it] == '1') {
        int x = *it;
        bool w = false;
        for (int y = x; y; y = cp[y]) {
            if (src[y] + dist(x, y) <= k) { w  = true; break; } // already infected
        }
        if (w) continue;
        if (!nx[x]) return -1;
        ++r;
        for (int y = nx[x]; y; y = cp[y]) src[y] = min(src[y], dist(nx[x], y));
    }
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> s;
    s.insert(s.begin(), '\0');
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 1);
    build();
    decompose(1, sz[1]);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j; j = cp[j]) v[j].push_back(i);
    }
    for (int i = 1; i <= n; i++) sort(v[i].begin(), v[i].end(), [=](int j, int k) { return dist(i, j) < dist(i, k); });
    o.resize(n);
    iota(o.begin(), o.end(), 1);
    sort(o.begin(), o.end(), [](int i, int j) { return d[i] < d[j]; });
    fill(cln, cln + N, inf);
    queue<int> bfs;
    for (int i = 1; i <= n; i++) if (s[i] == '0') cln[i] = 0, bfs.push(i);
    while (bfs.size()) {
        int x = bfs.front(); bfs.pop();
        for (int y : g[x]) if (cln[x] + 1 < cln[y]) bfs.push((cln[y] = cln[x] + 1, y));
    }
    int q; cin >> q;
    while (q--) cout << ac() << endl;
}
