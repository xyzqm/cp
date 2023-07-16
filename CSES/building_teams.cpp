#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 1;
vector<int> g[N];
int n, m, color[N];
bool dfs(int u, int c) {
    color[u] = c;
    for (int v : g[u]) {
        if (color[v] == c) return false;
        if (!color[v] && !dfs(v, 3 - c)) return false;
    }
    return true;
}
int main() {
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!color[i] && !dfs(i, 1)) cout << "IMPOSSIBLE" << endl;
        cout << color[i] << " ";
    }
    cout << endl;
}