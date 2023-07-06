// code assumes p[i] < i
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define UPD(a, b) a = min(a, b)
using namespace std;
const int N = 5e5;
const int K = 20;
int n, q, i1 = -1, a[2 * N], ind[2 * N], stl[2 * N][K], str[2 * N][K];
vector<int> g[N];
void dfs(int x) {
    if (!g[x].size()) a[ind[x] = ++i1] = x;
    for (int y : g[x]) {
        a[++i1] = x;
        if (ind[x] < 0) ind[x] = i1;
        dfs(y);
    }
}
int main() {
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }
    fill(ind, ind + 2 * N, -1);
    dfs(0);
    for (int i = 0; i <= i1; i++) stl[i][0] = str[i][0] = a[i];
    for (int k = 1; k < K; k++) {
        for (int i = 0; i <= i1; i++) {
            stl[i][k] = stl[i][k - 1];
            if (int j = i + (1 << (k - 1)); j <= i1) UPD(stl[i][k], stl[j][k - 1]);
            str[i][k] = str[i][k - 1];
            if (int j = i - (1 << (k - 1)); j >= 0) UPD(str[i][k], str[j][k - 1]);
        }
    }
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u = ind[u], v = ind[v];
        if (u > v) swap(u, v);
        int k = log2(v - u + 1);
        cout << min(stl[u][k], str[v][k]) << endl;
    }
}