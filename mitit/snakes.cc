#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 2;
int n, m, g[N][N], h[N][N], v[N][N],  sq[N][N], ph[N][N], pv[N][N], psq[N][N];

void ch(int i, int j) {
    if (j > m - 2) return;
    for (int k = j; k < j + 3; k++) if (g[i][k] != g[i][j]) return;
    h[i][j] = 1;
}

void cv(int i, int j) {
    if (i > n - 2) return;
    for (int k = i; k < i + 3; k++) if (g[k][j] != g[i][j]) return;
    v[i][j] = 1;
}

void csq(int i, int j) {
    if (i > n - 1 || j > n - 1) return;
    for (int k = i; k < i + 2; k++) {
        for (int h = j; h < j + 2; h++) if (g[k][h] != g[i][j]) return;
    }
    sq[i][j] = 1;
}

void pref(int a[N][N], int p[N][N]) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
           p[i][j] += p[i - 1][j];
           p[i][j] += p[i][j - 1];
           p[i][j] -= p[i - 1][j - 1];
           p[i][j] += a[i][j];
        }
    }
}

int c(int p[N][N], int l, int i, int r, int j) {
    if (l > r || i > j) return 0;
    return p[j][r] - p[i - 1][r] - p[j][l - 1] + p[i - 1][l - 1];
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> g[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) ch(i, j), cv(i, j), csq(i, j);
    pref(h, ph), pref(v, pv), pref(sq, psq);
    // for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cout << ph[i][j] << " \n"[j == m];
    int q; cin >> q;
    while (q--) {
        int i, l, j, r; cin >> i >> l >> j >> r;
        ++i, ++l, ++j, ++r;
        bool f = 0;
        for (auto p : {ph, pv, psq}) {
            f = f || c(p, l, i, r, j);
        }
        cout << vector{"YES", "NO"}[c(ph, l, i, r - 2, j) || c(pv, l, i, r, j - 2) || c(psq, l, i, r - 1, j - 1)] << endl;
    }
}
