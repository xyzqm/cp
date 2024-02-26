#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 1;
vector<int> adj[N];
bool vis[N];
int n, m;
void dfs(int x) {
    if (vis[x]) return;
    vis[x] = true;
    for (int y : adj[x]) dfs(y);
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> res;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            res.push_back(i);
            dfs(i);
        }
    }
    cout << res.size() - 1 << endl;
    for (int i = 0; i < res.size() - 1; i++) cout << res[i] << " " << res[i + 1] << endl;
}