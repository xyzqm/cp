#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
const int N = 2e5 + 1;
#else
#define DBG(X) println(#X": {}", X)
const int N = 14;
#endif

#define int int64_t

const int M = 1e9 + 7;
int inv(int x) {
    assert(x > 0);
    int r = 1;
    for (int pw = M - 2; pw; pw >>= 1, x = x * x % M) if (pw & 1) r = r * x % M;
    return r;
}

void ad(int &a, const int b) { a = (a + b) % M;}
int sb(int x) { return x < 0 ? x + M : x; }

const int K = 20;

int fa[N], up[N], tot_up[N], down[N], dep[N], deg[N], ivs[N], jmp[N][K], sm[N][K], cur[N];
vector<int> g[N];
// dep[i] = # of ancestors of i
// deg[i] = # of children of i
// up[i] = (dep[i] + 1)/dep[i] * (1 + avg up[child])

using sgt = array<int, 3>; // {number of elts in segment, expected time to get out * number of elts, number of elts left}
sgt operator+(const sgt a, const sgt b) {
    return {
        a[0] + b[0],
        ((a[0] * b[1] % M * ivs[a[2]] % M) + a[1] + b[1]) % M,
        b[2]
    };
}

sgt lift[N][K];

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        cin >> fa[i];
        jmp[i][0] = fa[i];
        dep[i] = dep[fa[i]] + 1;
        ++deg[fa[i]];
        g[fa[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) ivs[i] = inv(i);

    // compute up
    for (int i = n; i; i--) {
        if (!deg[i]) up[i] = 1;
        else if (dep[i]) up[i] = (dep[i] + 1) * ivs[dep[i]] % M * (1 + tot_up[i] * ivs[deg[i]] % M) % M;
        lift[i][0] = {1, up[i], dep[i]};
        ad(tot_up[fa[i]], up[i]);
    }
    DBG(up);

    // compute down
    auto dfs_down = [&](int u, auto &&f) -> void {
        if (fa[u]) {
            DBG(u);
            DBG(cur[fa[u]]);
            down[u] = sb(tot_up[fa[u]] - up[u]) + (deg[fa[u]] - 1) * (1 + cur[fa[u]] * ivs[dep[u]] % M) + 1;
            down[u] %= M;
            sm[u][0] = down[u];
        }
        cur[u] = cur[fa[u]];
        ad(cur[u], down[u] * dep[u]);
        for (int v : g[u]) {
            f(v, f);
        }
    };
    cur[1] = 0;
    dfs_down(1, dfs_down);

    DBG(down);

    // binary lift
    for (int k = 0; k + 1 < K; k++) {
        for (int i = 1; i <= n; i++) {
            int nx = jmp[i][k];
            jmp[i][k + 1] = jmp[nx][k];
            lift[i][k + 1] = lift[i][k] + lift[nx][k];
            sm[i][k + 1] = (sm[i][k] + sm[nx][k]) % M;
        }
    }

    while (q--) {
        int x, y; cin >> x >> y;
        int res = 0, og = dep[x];
        if (dep[y] > dep[x]) for (int k = K; k --> 0; ) if ((dep[y] - dep[x]) >> k & 1) {
            ad(res, sm[y][k]);
            y = jmp[y][k];
        }
        if (x == 1) assert(x == y);
        if (x == y) {
            cout << res << endl;
            continue;
        }
        // we have to jump up
        sgt cur = {0, 0, 0};
        ad(res, up[x]);
        x = fa[x];
        if (dep[x] < dep[y]) ad(res, down[y]), y = fa[y];

        if (dep[x] > dep[y]) for (int k = K; k --> 0; ) if ((dep[x] - dep[y]) >> k & 1) {
            cur = cur + lift[x][k];
            x = jmp[x][k];
        }
        for (int k = K; k --> 0; ) if (jmp[x][k] != jmp[y][k]) {
            cur = cur + lift[x][k];
            ad(res, sm[y][k]);
            x = jmp[x][k];
            y = jmp[y][k];
        }
        if (x != y) {
            cur = cur + lift[x][0];
            ad(res, down[y]);
            x = fa[x];
        }
        DBG(cur);
        ad(res, cur[1] * ivs[og] % M);
        ad(res, (::cur[x] * ivs[dep[x] + 1] % M));
        cout << res << endl;
    }
}
