// https://qoj.ac/problem/4054
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
const int inf = 1e14;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

/**
dp[u][v] = min cost to move hole to u and move v to hole
    - does NOT include the contribution of either the hole or node v

need to precompute several quantities:
from_l[x][0/1]: min cost to put hole/u into left subtree and get x out, deleting only left
    - min(cost[u][_] + dp[_][x])
    - does not include cost of x
from_r[y][0/1]: min cost to put hole/u into left subtree, get node y out of right subtree
    - min(from_l[x] + cost[x][_] + dp[_][y]) where _, y are in right subtree
    - x/_ dim can be precomputed separately

answer is min(dp[x][y] + cost[u][x] + cost[y][u])
*/

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int> w(n + 1), fa(n + 1);
    // also maintain undirected graph so we don't have to calculate lca for distance
    vector<vector<int>> ch(n + 1), g(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 2; i <= n; i++) {
        cin >> fa[i];
        ch[fa[i]].push_back(i);
        g[fa[i]].push_back(i);
        g[i].push_back(fa[i]);
    }

    // calculate costs of moving each val to a node
    auto cost = vector(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        auto calc = [&](this auto calc, int u, int p) -> void {
            if (p) cost[i][u] = cost[i][p] + w[i];
            for (int v : g[u]) if (v != p) calc(v, u);
        };
        calc(i, 0);
    }
    DBG(cost);

    // calculate pairs with a given LCA
    vector<vector<int>> sub(n + 1);
    vector<vector<array<int, 2>>> on(n + 1);
    auto dfs = [&](this auto dfs, int u) -> void {
        sub[u] = {u};
        on[u].push_back({u, u});
        for (int v : ch[u]) {
            dfs(v);
            for (int x : sub[u]) for (int y : sub[v]) {
                on[u].push_back({x, y});
                on[u].push_back({y, x});
            }
            sub[u].append_range(sub[v]);
        }
    };
    dfs(1);
    DBG(on);

    // the actual dp
    auto smin = [](int &a, int b) { a = min(a, b); };

    // dp arrays for precomp
    auto dp = vector(n + 1, vector<int>(n + 1, inf));
    vector<array<int, 2>> from_l(n + 1);
    vector<int> into_r(n + 1), swap_r(n + 1), to_r(n + 1);

    auto ac = [&](this auto ac, int u) -> void {
        for (int v : ch[u]) ac(v);
        if (ch[u].size() == 0) dp[u][u] = 0; // leaf
        else if (ch[u].size() == 1) {
            for (auto [x, y] : on[ch[u][0]]) {
                // swap hole and u first
                smin(dp[x][u], dp[x][y] + cost[y][u]);
                // swap hole and u second
                smin(dp[u][y], dp[x][y] + cost[u][x]);
            }
        }
        else for (int _ : {0, 1}) {
            // assume left always deleted before right
            int lc = ch[u][0], rc = ch[u][1];
            for (int x : sub[lc]) {
                from_l[x] = {inf, inf};
                into_r[x] = inf;
            }
            for (int y : sub[rc]) {
                to_r[y] = swap_r[y] = inf;
            }
            // take x out of L
            for (auto [_, x] : on[lc]) for (int t : {0, 1}) {
                smin(from_l[x][t], t * cost[u][_] + dp[_][x]);
            }
            // take _ out of L and put it in y
            for (int x : sub[lc]) for (int y : sub[rc]) {
                smin(to_r[y], from_l[x][1] + cost[x][y]);
            }

            // min cost to move hole from u to y
            for (auto [y, _] : on[rc]) {
                smin(swap_r[y], dp[y][_] + cost[_][u]);
            }

            // put x into R
            for (int x : sub[lc]) for (int _ : sub[rc]) {
                smin(into_r[x], cost[x][_] + swap_r[_]);
            }

            // case 1: hole---u deleted first
            for (auto [x, _] : on[lc]) {
                smin(dp[x][u], dp[x][_] + into_r[_]);
            }

            // case 2: hole---u deleted second
            for (int x : sub[lc]) for (int y : sub[rc]) {
                smin(dp[y][x], from_l[x][1] + swap_r[y]);
            }

            // case 3: hole---u deleted last
            for (auto [_, y] : on[rc]) {
                smin(dp[u][y], to_r[_] + dp[_][y]);
            }

            ranges::reverse(ch[u]);
        }
    };
    ac(1);
    DBG(dp);
    int ans = inf;
    for (auto [x, y] : on[1]) smin(ans, dp[x][y] + cost[1][x] + cost[y][1]);
    cout << ans << endl;
}
