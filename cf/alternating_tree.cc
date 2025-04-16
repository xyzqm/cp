// https://codeforces.com/problemset/problem/960/E
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
const int M = 1e9 + 7;
const int N = 2e5 + 1;
#define eq(a, op, b) a = a op (b)

struct mint {
    int v;
    mint() : v(0) {}
    mint(int v) : v((v % M + M) % M) {}
    operator int() { return v; }
};

vector<int> g[N];
mint w[N][2], v[N]; // # of ways for node to have paths to subtree with even/odd # of nodes
mint r = 0;
int n, sz[N];

void cp(int x, int p) {
    for (int y : g[x]) if (y != p) {
        cp(y, x);
        eq(sz[x], +, sz[y]);
        for (int t : {0, 1}) eq(w[x][t], +, w[y][t ^ 1]);
    }
    eq(w[x][1], +, 1);
    eq(sz[x], +, 1);
}

void rr(int x, int p) {
    mint mul = n; // n paths where this is the first node
    for (int y : g[x]) { // put start of path in this subtree
        eq(mul, +, (w[y][0] - w[y][1]) * (n - sz[y]));
        if (y != p) { // reroot
            mint a = w[x][1], b = w[x][0], c = w[y][1], d = w[y][0];
            int szx = sz[x], szy = sz[y];
            eq(w[x][1], -, w[y][0]);
            eq(w[x][0], -, w[y][1]);
            w[y][0] = a;
            w[y][1] = b;
            sz[x] = szx - szy;
            sz[y] = szx;
            rr(y, x);
            tie(w[x][1], w[x][0]) = {a, b};
            tie(w[y][1], w[y][0]) = {c, d};
            tie(sz[x], sz[y]) = {szx, szy};
        }
    }
    eq(r, +, mul * v[x]);
}

int32_t main() {
    cin >> n;
    for (int i = 1; i <= n; i++) { int x; cin >> x; v[i] = x; }
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cp(1, 0);
    rr(1, 0);
    cout << r << endl;
}
