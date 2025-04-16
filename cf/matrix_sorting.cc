// https://codeforces.com/contest/1500/problem/C
#include <bits/stdc++.h>
using namespace std;

#define loop(i, n) for (int i = 0; i < n; i++)
#define exit() { cout << -1 << endl; return 0; }

const int N = 3005;
int n, m;
array<int, N> a[N], b[N], d;
vector<int> g[N];

void di(int u, int v) { g[u].push_back(v), ++d[v]; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    map<array<int, N>, vector<int>> mp;
    loop(i, n) {
        loop(j, m) cin >> a[i][j];
        mp[a[i]].push_back(i);
    }
    for (auto &[_, v] : mp) sort(v.begin(), v.end(), greater<int>());
    loop(i, n) {
        loop(j, m) cin >> b[i][j];
        if (!mp[b[i]].size()) exit(); // rows don't match up
        int x = mp[b[i]].back();
        mp[b[i]].pop_back();
        b[i][m] = x;
    }
    for (int j = 0; j <= m; j++) {
        for (int i = 0; i + 1 < n; i++) {
            if (b[i][j] > b[i + 1][j]) di(i, n + j);
            else if (b[i][j] < b[i + 1][j]) di(n + j, i);
        }
    }
    queue<int> bfs;
    for (int i = n; i <= n + m; i++) if (!d[i]) bfs.push(i); // only start from column nodes
    vector<int> ord;
    while (bfs.size()) {
        int x = bfs.front(); bfs.pop();
        for (int y : g[x]) if ((y < n && d[y]) || !--d[y]) d[y] = 0, bfs.push(y);
        if (x >= n) ord.push_back(x - n + 1);
    }
    if (ord.size() <= m) exit();
    auto it = find(ord.begin(), ord.end(), m + 1);
    if (it != ord.end()) ord.erase(it, ord.end());
    reverse(ord.begin(), ord.end());
    cout << ord.size() << endl;
    for (int x : ord) cout << x << " ";
    cout << endl;
}
