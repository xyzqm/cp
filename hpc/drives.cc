#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    int n, m; cin >> n >> m;
    auto grid = vector(n + 2, vector<char>(m + 2, '#'));
    array<int, 2> h, b;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'H') h = {i, j};
            if (grid[i][j] == 'B') b = {i, j};
        }
    }
    vector<array<int, 2>> dir = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}
    };
    auto vis = vector(n + 1, vector(m + 1, array<bool, 4>()));
    deque<array<int, 4>> dq;
    for (int i = 0; i < 4; i++) dq.push_back({h[0], h[1], i, 0});
    while (dq.size()) {
        auto [r, c, d, dist] = dq.front(); dq.pop_front();
        if (grid[r][c] == '#' || vis[r][c][d]) continue;
        vis[r][c][d] = true;
        if (b == array{r, c}) { cout << dist << endl; return 0; }
        for (int nx = 0; nx < 4; nx++) dq.push_back({r, c, nx, dist + 1});
        dq.push_front({r + dir[d][0], c + dir[d][1], d, dist});
    }
    cout << "Impossible" << endl;
}
