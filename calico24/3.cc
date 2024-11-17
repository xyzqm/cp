#include <bits/stdc++.h>
#include <numeric>
using namespace std;

const int N = 100;
int n, m, f[N];
char a[N][N];
void ac() {
    cin >> n >> m;
    fill(f, f + m, 0);
    int r = 0, t = 0;
    for (int i = 0; i < n; i++) {
        bool w = false;
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            w = w || a[i][j] == '#';
            f[j] = f[j] || a[i][j] == '#';
            t += (a[i][j] == '#');
        }
        r += w;
    }
    if (t == r * accumulate(f, f + m, 0)) cout << "ferb\n";
    else cout << "phineas\n";
}

int main() {
    int t; cin >> t;
    while (t--) ac();
}
