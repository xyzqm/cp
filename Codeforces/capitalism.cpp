// https://codeforces.com/problemset/problem/1450/E
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dist(n, vector<int>(n, 1e6));
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--, b--;
        if (c == 0) {
            dist[a][b] = dist[b][a] = 1;
        }
        else dist[a][b] = 1, dist[b][a] = -1;
    }
    vector<int> color(n, -1);
    queue<int> q;
    color[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < n; i++) {
            if (dist[x][i] != 1e6 && i != x) {
                if (color[i] == -1) {
                    color[i] = 1 - color[x];
                    q.push(i);
                } else if (color[i] != 1 - color[x]) {
                    cout << "NO" << endl;
                    return 0;
                }
            }
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != 1e6 && dist[k][j] != 1e6)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    for (int i = 0; i < n; i++) if (dist[i][i] < 0) {
        cout << "NO" << endl;
        return 0;
    }
    int ans = 0, u;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] != 1e6 && dist[i][j] >= ans) {
                ans = dist[i][j], u = i;
            }
        }
    }
    cout << "YES" << endl;
    cout << ans << endl;
    for (int i = 0; i < n; i++) {
        cout << dist[u][i] << " ";
    }
    cout << endl;
}