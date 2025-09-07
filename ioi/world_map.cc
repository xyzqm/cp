#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> create_map(int N, int M, vector<int> A, vector<int> B) {
    auto g = vector(N + 1, vector<int>());
    for (auto [u, v] : views::zip(A, B)) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> dep(N + 1, -1), et;
    auto dfs = [&](this auto dfs, int x = 1, int d = 0) -> void {
        dep[x] = d;
        et.push_back(x);
        for (int y : g[x]) if (dep[y] < 0) {
            dfs(y, d + 1);
            et.push_back(x);
        }
    };
    dfs();
    vector<vector<int>> diags;
    auto add_diag = [&](int v) {
        diags.emplace_back(min(diags.size() + 1, 4 * N - diags.size() - 1), v);
    };
    vector<int> vis(N + 1);
    for (int x : et) {
        add_diag(x);
        if (!vis[x]++) {
            add_diag(x);
            copy_if(g[x].begin(), g[x].end(), diags.back().begin(), [&](int y) { return dep[y] < dep[x]; });
            add_diag(x);
        }
    }
    auto grid = vector(2 * N, vector(2 * N, 0));
    for (int i = 0; auto &d : diags) {
        for (int j = i, k = 0, l = 0; j >= 0; j--, k++) if (j < 2 * N && k < 2 * N) grid[j][k] = d[l++];
        i++;
    }
    return grid;
}

#ifndef ONLINE_JUDGE
int32_t main() {
    println("{}", create_map(3, 2, {1, 2}, {2, 3}));
}
#endif
