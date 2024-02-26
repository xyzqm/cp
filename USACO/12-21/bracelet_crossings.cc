#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define int long long
const int inf = 1e18;
const int N = 50;
vector<int> c[N];
int n, m;
bool cont(int X) { // checks whether shape X is continuous
    int s = -1;
    for (int i = 0; i < m; i++) {
        bool C = false;
        for (int j : c[i]) C = C || j == X;
        if (s == -1) { if (C) s = 0; }
        else if (s == 0) { if (!C) s = 1; }
        else if (s == 1) { if (C) return false; }
    }
    return true;
}
bool below(int X, int Y) { // true if X is fully below Y
    for (int i = 0; i < m; i++) {
        int x = -1, y = inf;
        for (int j = 0; j < c[i].size(); j++) {
            if (c[i][j] == X) x = max(x, j);
            if (c[i][j] == Y) y = min(y, j);
        }
        if (x > y) return false;
    }
    return true;
}
bool in(int X, int Y) { // checks whether shape X is within Y
    for (int i = 0; i < m; i++) {
        int ly = inf, lx = inf, rx = -1, ry = -1;
        for (int j = 0; j < c[i].size(); j++) {
            if (c[i][j] == X) lx = min(lx, j), rx = max(rx, j);
            if (c[i][j] == Y) ly = min(ly, j), ry = max(ry, j);
        }
        if (ly > lx || rx > ry) return false;
    }
    return true;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int k; cin >> k;
            c[i].resize(k);
            for (int& j : c[i]) cin >> j;
        }
        bool w = true;
        for (int i = 1; i <= n; i++) {
            w = w && cont(i);
            for (int j = i + 1; j <= n; j++) {
                w = w && (in(i, j) || in(j, i) || below(i, j) || below(j, i));
                if (!w) break;
            }
        }
        cout << (w ? "YES" : "NO") << "\n";
    }
    return 0;
}