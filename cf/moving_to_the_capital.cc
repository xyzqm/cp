// https://codeforces.com/contest/1472/problem/G
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 1;
int n, m, d[N], dp[N], order[N];
vector<int> adj[N];
bool cmp(int i, int j) {
    return d[i] > d[j];
}
int main() {
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            d[i] = INT_MAX;
        }
        for (int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
        }
        queue<pair<int, int>> bfs;
        bfs.push({1, 0});
        while (!bfs.empty()) {
            int x, dist; tie(x, dist) = bfs.front();
            bfs.pop();
            if (dist >= d[x]) continue;
            d[x] = dist;
            for (int y : adj[x]) {
                if (dist + 1 < d[y]) bfs.push({y, dist + 1});
            }
        }
        for (int i = 1; i <= n; i++) {
            dp[i] = d[i];
            for (int j : adj[i]) {
                dp[i] = min(dp[i], d[j]);
            }
        }
        iota(order, order + n, 1);
        sort(order, order + n, cmp);
        for (int i = 0; i < n; i++) {
            int x = order[i];
            for (int y : adj[x]) {
                if (d[y] > d[x]) dp[x] = min(dp[x], dp[y]);
            }
        }
        for (int i = 1; i <= n; i++) {
            cout << dp[i] << " ";
        }
        cout << endl;
    }
}