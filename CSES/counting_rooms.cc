#include <iostream>
using namespace std;
const int N = 1000;
int n, m;
int d1[]{1, -1, 0, 0};
int d2[]{0, 0, 1, -1};
char grid[N][N];
bool surrounded = false;
bool val(int x, int y) {
    return min(x, y) >= 0 && x < n && y < m && grid[x][y] == '.';
}
void dfs(int x, int y) {
    for (int i = 0; i < 4; i++) {
        int nx = x + d1[i], ny = y + d2[i];
        if (val(nx, ny)) {
            grid[nx][ny] = 'X';
            dfs(nx, ny);
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> grid[i][j];
    int ans = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        if (grid[i][j] == '.') {
            // for (int I = 0; I < n; I++) {
            //     for (int J = 0; J < m; J++) {
            //         cout << grid[I][J];
            //     }
            //     cout << endl;
            // }
            // cout << "----------\n";
            surrounded = true;
            grid[i][j] = 'X';
            dfs(i, j);
            if (surrounded) ++ans;
        }
    }
    cout << ans << endl;
}