#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 1;
const int A = 10;
const int K = 20;
int n, m, q, P[N], D[N], J[N][K];
vector<int> g[N];
vector<int> S[N][K];
void mg(vector<int>& a, const vector<int>& b) {
    vector<int> c(a.size() + b.size());
    merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
    c.erase(unique(c.begin(), c.end()), c.end());
    a = c;
}
void dfs(int x, int p) {
    D[x] = D[p] + 1;
    J[x][0] = p;
    for (int i = 1; i < K; i++) {
        J[x][i] = J[J[x][i - 1]][i - 1];
        mg(S[x][i], S[J[x][i - 1]][i - 1]);
        mg(S[x][i], S[x][i - 1]);
        while (S[x][i].size() > A) S[x][i].pop_back();
    }
    for (int y : g[x]) if (y != p) dfs(y, x);
}
vector<int> jmp(int& x, int d) {
    vector<int> ans;
    for (int i = 0; i < K; i++) if ((d >> i) & 1) {
        mg(ans, S[x][i]);
        while (ans.size() > A) ans.pop_back();
        x = J[x][i];
    }
    return ans;
}
vector<int> solve(int u, int v) {
    vector<int> ans;
    if (D[u] < D[v]) mg(ans, jmp(v, D[v] - D[u]));
    else if (D[u] > D[v]) mg(ans, jmp(u, D[u] - D[v]));
    if (u == v) {
        mg(ans, S[u][0]);
        while (ans.size() > A) ans.pop_back();
        return ans;
    }
    for (int k = K - 1; k >= 0; --k) {
        if (J[u][k] != J[v][k]) {
            mg(ans, S[u][k]);
            mg(ans, S[v][k]);
            while (ans.size() > A) ans.pop_back();
            u = J[u][k];
            v = J[v][k];
        }
    }
    mg(ans, S[u][1]);
    mg(ans, S[v][1]);
    while (ans.size() > A) ans.pop_back();
    return ans;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= m; i++) {
        int c;
        cin >> c;
        if (S[c][0].size() < A) S[c][0].push_back(i);
    }
    dfs(1, 0);
    while (q--) {
        int u, v, a;
        cin >> u >> v >> a;
        vector<int> ans = solve(u, v);
        while (ans.size() > a) ans.pop_back();
        cout << ans.size() << " ";
        for (int x : ans) cout << x << " ";
        cout << endl;
    }
}
