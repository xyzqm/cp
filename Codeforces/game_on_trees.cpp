// https://codeforces.com/problemset/problem/280/C
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 1;
vector<int> adj[N];
double ans = 0;
void dfs(int x, int p, int d) {
    ans += 1.0 / d;
    for (int y : adj[x]) {
        if (y != p) dfs(y, x, d + 1);
    }
}
int main() {
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0, 1);
    cout << fixed << setprecision(6) << ans << endl;
}