// https://codeforces.com/problemset/problem/1092/F
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 1;
vector<int> adj[N];
int n;
ll v[N], s[N], ans, res;
ll dfs1(int x, int p, int d) {
    res += d * v[x];
    for (int y : adj[x]) {
        if (y != p) s[x] += dfs1(y, x, d + 1);
    }
    return s[x] += v[x];
}
void dfs2(int x, int p) {
    for (int y : adj[x]) {
        if (y == p) continue;
        ll ox = s[x], oy = s[y], og = res;
        s[x] -= s[y];
        res += s[x] - s[y];
        ans = max(ans, res);
        s[y] = ox;
        dfs2(y, x);
        s[x] = ox, s[y] = oy, res = og;
    } 
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> v[i];
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(1, 0, 0);
    ans = res;
    dfs2(1, 0);
    cout << ans << endl;
}