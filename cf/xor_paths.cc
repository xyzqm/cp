#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int N = 20;
map<ll, ll> path1[N], path2[N];
int n, m;
ll k, grid[N][N];
struct state {
    int x, y;
    ll v;
};
int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> grid[i][j];
    }
    queue<state> bfs;
    bfs.push({0, 0, grid[0][0]});
    while (!bfs.empty()) {
        state cur = bfs.front();
        bfs.pop();
        if (cur.x + cur.y == (n + m - 2) / 2) {
            path1[cur.x][cur.v]++;
            continue;
        }
        if (cur.x + 1 < n) {
            bfs.push({cur.x + 1, cur.y, cur.v ^ grid[cur.x + 1][cur.y]});
        }
        if (cur.y + 1 < m) {
            bfs.push({cur.x, cur.y + 1, cur.v ^ grid[cur.x][cur.y + 1]});
        }
    }
    bfs.push({n - 1, m - 1, 0});
    while (!bfs.empty()) {
        state cur = bfs.front();
        bfs.pop();
        if (cur.x + cur.y == (n + m - 2) / 2) {
            path2[cur.x][cur.v]++;
            continue;
        }
        if (cur.x - 1 >= 0) {
            bfs.push({cur.x - 1, cur.y, cur.v ^ grid[cur.x][cur.y]});
        }
        if (cur.y - 1 >= 0) {
            bfs.push({cur.x, cur.y - 1, cur.v ^ grid[cur.x][cur.y]});
        }
    }
    ll ans = 0;
    for (int i = 0; i <= (n + m - 2) / 2; i++) {
        for (auto p : path1[i]) {
            ans += p.second * path2[i][k ^ p.first];
        }
    }
    cout << ans;
}