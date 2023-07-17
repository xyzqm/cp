#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>
using namespace std;
const int N = 2e5 + 1;
const int K = 19;
vector<int> ord, adj[N + 1];
int n, q, ind[N], d[N], stl[2 * N][K], str[2 * N][K];
void dfs(int x, int p) {
    d[x] = d[p] + 1;
    if (!(adj[x].size() - (p > 0))) {
        ind[x] = ord.size();
        ord.push_back(x);
    } else for (int y : adj[x]) if (y != p) {
        ind[x] = ord.size();
        ord.push_back(x);
        dfs(y, x);
    }
}
inline int MIN(int x, int y) {
    return d[x] < d[y] ? x : y;
}
inline int lca(int x, int y) {
    int l = ind[x], r = ind[y];
    if (l > r) swap(l, r);
    int k = log2(r - l + 1);
    return MIN(stl[l][k], str[r][k]);
}
int main() {
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    } 
    dfs(1, 0);
    for (int i = 0; i < ord.size(); i++) stl[i][0] = str[i][0] = ord[i];
    for (int k = 1; k < K; k++) {
        for (int i = 0; i < ord.size(); i++) {
            stl[i][k] = stl[i][k - 1];
            if (int j = i + (1 << (k - 1)); j < ord.size()) stl[i][k] = MIN(stl[i][k], stl[j][k - 1]);
            str[i][k] = str[i][k - 1];
            if (int j = i - (1 << (k - 1)); j >= 0) str[i][k] = MIN(str[i][k], str[j][k - 1]);
        }
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << endl;
    }
}