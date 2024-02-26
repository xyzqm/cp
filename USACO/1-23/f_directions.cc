#include <bits/stdc++.h>
using namespace std;
const int N = 1500;
char dirs[N][N];
bool vis[N][N];
int cows[N][N];
int n;
struct vat {
    int x, y, val;
    vat(int x, int y, int val) {
        this->x = x;
        this->y = y;
        this->val = val;
    }
};
queue<vat> bfs;
vector<vat> vats;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dirs[i][j];
        }
        int v; cin >> v;
        vats.push_back(vat(i, n, v));
    }
    for (int i = 0; i < n; i++) {
        int v; cin >> v;
        vats.push_back(vat(n, i, v));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cows[i][j] = 1;
            if (i && dirs[i - 1][j] == 'D') cows[i][j] += cows[i - 1][j];
            if (j && dirs[i][j - 1] == 'R') cows[i][j] += cows[i][j - 1];
        }
    }
    int ans = 0;
    for (vat vat : vats) {
        if (vat.y == n && dirs[vat.x][vat.y - 1] == 'R') ans += vat.val * cows[vat.x][vat.y - 1];
        else if (vat.x == n && dirs[vat.x - 1][vat.y] == 'D') ans += vat.val * cows[vat.x - 1][vat.y];
    }
    cout << ans << endl;
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b, x, y; cin >> a >> b;
        a--, b--;
        x = a, y = b;
        ans = 0;
        while (x < n && y < n) {
            if (dirs[x][y] == 'R') y++;
            else x++;
            if (x < n && y < n) cows[x][y] -= cows[a][b];
        }
        x = a, y = b;
        dirs[x][y] = ((dirs[x][y] == 'D') ? 'R' : 'D');
        while (x < n && y < n) {
            if (dirs[x][y] == 'R') y++;
            else x++;
            if (x < n && y < n) cows[x][y] += cows[a][b];
        }
        for (vat vat : vats) {
            if (vat.y == n && dirs[vat.x][vat.y - 1] == 'R') ans += vat.val * cows[vat.x][vat.y - 1];
            else if (vat.x == n && dirs[vat.x - 1][vat.y] == 'D') ans += vat.val * cows[vat.x - 1][vat.y];
        }
        cout << ans << endl;
    }
}