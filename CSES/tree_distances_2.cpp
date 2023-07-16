#include <iostream>
#include <vector>
using namespace std;
#define int long long
const int N = 2e5 + 1;
int n, s[N], ans[N], D = 0;
vector<int> adj[N];
void dfs1(int x, int p, int d) {
    D += d;
    for (int y : adj[x]) if (y != p) {
        dfs1(y, x, d + 1);
        s[x] += s[y];
    }
}
void dfs2(int x, int p) {
    if (p) {
        D += (s[p] -= s[x]) - s[x];
        s[x] = n;
    }
    ans[x] = D;
    for (int y : adj[x]) if (y != p) dfs2(y, x);
    if (p) {
        D -= s[p] - (s[x] = n - s[p]);
        s[p] = n;
    }
}
signed main() {
    fill(s, s + N, 1);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(1, 0, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;
}