#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 1;
vector<int> adj[N];
int n, dist[N], ans[N], mx = 0;
void dfs(int x, int p) {
    ans[x] = max(ans[x], dist[x] = dist[p] + 1);
    if (dist[x] > dist[mx]) mx = x;
    for (int y : adj[x]) if (y != p) dfs(y, x);
}
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dist[0] = -1;
    dfs(1, 0);
    dfs(mx, 0);
    dfs(mx, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;
}