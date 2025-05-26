// https://contest.x-camp.org/contest/425/problem/2180
// Turing Cup 2025, Intermediate B
#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 1e6 + 1;

int n, m, q, o, cc[N], zero[N], lcf[N];
__int128 len[N];
bitset<N> v;
vector<array<int, 2>> g[N];

__int128 GCD(__int128 a, __int128 b) {
    while (b != 0) tie(a, b) = make_pair(b, a % b);
    return a;
}

int cur = 0; // current component
void dfs(int x) {
    v[x] = 1, cc[x] = cur;
    for (auto [y, w] : g[x]) {
        if (!v[y]) len[y] = len[x] + w, dfs(y);
        else lcf[cur] = GCD(lcf[cur], w + len[x] - len[y]);
    }
}

void dfs2(int x) {
    v[x] = 1, zero[x] = cur;
    for (auto [y, w] : g[x]) if (!v[y] && !w) dfs2(y);
}

int32_t main() {
    cin >> n >> m >> q >> o;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    for (int i = 1; i <= n; i++) if (!v[i]) ++cur, dfs(i);
    v = 0;
    for (int i = 1; i <= n; i++) if (!v[i]) ++cur, dfs2(i);
    while (q--) {
        int u, v, w; cin >> u >> v >> w;
        bool yes;
        if (!w) yes = (zero[u] == zero[v]);
        else yes = (cc[u] == cc[v] && (len[u] + len[v]) % gcd(lcf[cc[u]], w) == 0);
        cout << (yes ? "bougain" : "villea") << endl;
    }
}
