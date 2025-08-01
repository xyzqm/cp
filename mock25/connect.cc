#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 1;

int fa[N];

int rt(int x) { return x == fa[x] ? x : (fa[x] = rt(fa[x])); }
bool U(int x, int y) {
    x = rt(x), y = rt(y);
    if (x == y) return false;
    fa[x] = y;
    return true;
}

int main() {
    int n, m; cin >> n >> m;
    iota(fa, fa + N, 0);
    for (int i = 0; i <= m; i++) {
        if (n == 1) {
            cout << i << endl;
            exit(0);
        }
        if (i == m) {
            cout << -1 << endl;
            exit(0);
        }
        int u, v; cin >> u >> v;
        n -= U(u, v);
    }
}
