#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int N = 4e5 + 1;
int t[N]; // the times of each node
int dep[N]; // depth of node in centroid decomp
int sz[N]; // size of each subtree
int down[N][2][2]; // # of possibilities when going down for a given arrival time
// 0 -> already stamped on way up|1-> not stamped yet
//
vector<int> g[N];
vector<array<int, 3>> ancs[N];

int get_sz(int x, int p) {
    sz[x] = 0;
    for (int y : g[x]) if (y != p && dep[y] == N) sz[x] += get_sz(y, x);
    return ++sz[x];
}

// up => min value of t_i - dist
// down => min value of t_i + dist
int upd(int x, int p, int centroid, int dist, int up, int down) {

}


void decompose(int x, int p, int n, int l) {
    for (int y : g[x]) if (y != p && dep[y] == N && sz[y] > n / 2) decompose(y, x, n, l);
    dep[x] = l;
    for (int y : g[x]) {
        decompose(y, x, get_sz(y, x), l + 1);
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, d; cin >> n >> d;
    for (int i = 1; i <= n; i++) cin >> t[i];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    fill(dep, dep + N, N);
}
