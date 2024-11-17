#include <bits/stdc++.h>
using namespace std;

struct T {
    int i, j;
    bool red;
    bool operator<(const T &o) const {
        return make_tuple(i, j, red) < make_tuple(o.i, o.j, o.red);
    }
};

int dx[]{1, -1, 0, 0};
int dy[]{0, 0, 1, -1};
int n, m;
int cnt(vector<vector<int>> &a, int i1, int j1, int i2, int j2) {
    if (i1 > i2 || j1 > j2) swap(i1, i2), swap(j1, j2);
    i1 = max(i1, 0), j1 = max(j1, 0);
    i2 = min(i2, n - 1);
    j2 = min(j2, m - 1);
    int r = a[i2][j2];
    if (i1 > 0) r -= a[i1 - 1][j2];
    if (j1 > 0) r -= a[i2][j1 - 1];
    if (min(i1, j1) > 0) r += a[i1 - 1][j1 - 1];
    return r;
};

void ac() {
    int K; cin >> n >> m >> K;
    vector<string> a(n);
    vector<vector<array<int, 2>>> vis(n, vector<array<int, 2>>(m, array<int, 2>()));
    vector<vector<int>> walls(n, vector<int>(m)), crystals(n, vector<int>(m));
    deque<pair<T, int>> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'S') q.push_back({{i, j, 1}, 0});
            walls[i][j] = (a[i][j] == '#');
            if (i > 0) walls[i][j] += walls[i - 1][j];
            if (j > 0) walls[i][j] += walls[i][j - 1];
            if (min(i, j) > 0) walls[i][j] -= walls[i - 1][j - 1];
            crystals[i][j] = (a[i][j] == '*');
            if (i > 0) crystals[i][j] += crystals[i - 1][j];
            if (j > 0) crystals[i][j] += crystals[i][j - 1];
            if (min(i, j) > 0) crystals[i][j] -= crystals[i - 1][j - 1];
        }
    }
    while (q.size()) {
        auto [st, v] = q.front();
        q.pop_front();
        auto [i, j, r] = st;
        if (vis[i][j][r]) continue;
        vis[i][j][r] = true;
        if (a[i][j] == '#') continue;
        if (a[i][j] == 'E') { cout << v << endl; return; }
        if (!r && a[i][j] == '*') { q.push_front({{i, j, 1}, v}); continue; }
        for (int k = 0; k < 4; k++) q.push_back({{i + dx[k], j + dy[k], r}, v + 1});
        if (r) {
            for (int k = 0; k < 4; k++) {
                int x = 0;
                for (int d = K; d > 0; d >>= 1) {
                    while (x + d <= K && !cnt(walls, i, j, i + dx[k] * (x + d), j + dy[k] * (x + d))) {
                        x += d;
                    }
                }
                if (!x) continue;
                bool f = cnt(crystals, i + dx[k], j + dy[k], i + x * dx[k], j + x * dy[k]);
                q.push_back({{i + x * dx[k], j + x * dy[k], f}, v + 1});
            }
        }
    }
    cout << -1 << endl;
}

int main() {
    int t; cin >> t;
    while (t--) ac();
}
