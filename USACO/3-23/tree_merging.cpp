#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
int N  = 0;
struct tree {
    int n;
    vector<vector<int>> adj;
    vector<int> p;
    vector<bool> exists;
    void input() {
        cin >> n;
        N = max(N, n);
        adj.assign(N + 1, vector<int>());
        p.assign(N + 1, 0);
        exists.assign(N + 1, false);
        for (int i = 1; i < n; i++) {
            int x; cin >> x >> p[x];
            exists[x] = exists[p[x]] = true;
            adj[p[x]].push_back(x);
        }
    }
    int root() {
        for (int i = 1; i <= N; i++) if (!p[i]) return i;
    }
} t1, t2;
bool solved[1001][1001];
vector<bool> vis(1001);
vector<pii> sol[1001];
int ans = 0;
bool solve(int a, int b, int d) {
    for (int x : t1.adj[a]) {
        if (t2.exists[x]) {
            if (t2.p[x] != b /*|| a == b*/) return false;
            else if (!solved[x][x]) {
                solved[x][x] = solve(x, x, d + 1);
                continue;
            }
        }
        bool merged = false;
        for (int y : t2.adj[b]) {
            if (x < y && solve(x, y, d + 1)) { // try merging x into y
                merged = true;
                if (a == b) t1.exists[x] = false;
                break;
            }
        }
        if (!merged && a != b) return false; // can't merge x into anything
    }
    return solved[a][b] = true;
}
bool fin(int a, int b, int d) {
    if (!solved[a][b]) return false;
    for (int x : t1.adj[a]) {
        if (t2.exists[x]) {
            if (!vis[x]) vis[x] = fin(x, x, d + 1);
            continue;
        }
        for (int y : t2.adj[b]) {
            if (x < y && fin(x, y, d + 1)) {
                ans++;
                sol[d].push_back({x, y});
                break;
            }
        }
    }
    return true;
}
int main() {
    int t; cin >> t;
    while (t--) {
        ans = N = 0;
        fill(vis.begin(), vis.end(), false);
        memset(solved, 0, sizeof solved);
        t1.input();
        t2.input();
        for (int i = 0; i < N; i++) sol[i].clear();
        int r = t1.root();
        solve(r, r, 0);
        fin(r, r, 0);
        cout << ans << endl;
        for (int i = 0; i < N; i++) for (auto& [a, b] : sol[i]) cout << a << " " << b << endl;
    }
}