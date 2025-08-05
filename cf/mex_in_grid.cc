#include <bits/stdc++.h>
using namespace std;

void ac() {
    int n; cin >> n;
    auto a = vector(n, vector(n, -1));
    int r = (n - 1) / 2, c = (n - 1) / 2;
    int dr = 0, dc = 1;
    for (int i = 0; i < n * n; i++) {
        a[r][c] = i;
        if (i == n * n - 1) break;
        r += dr, c += dc;
        int nr = dr, nc = dc;
        if (nr) nr = -nr;
        swap(nr, nc);
        // cout << r << " " << c << " " << nr << " " << nc << endl;
        if (a[r + nr][c + nc] == -1) dr = nr, dc = nc;
    }
    for (auto &v : a) {
        for (int &x : v) cout << x << " ";
        cout << endl;
    }
}

int main() {
    int t; cin >> t;
    while (t--) ac();
}
