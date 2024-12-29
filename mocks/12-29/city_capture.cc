#include <bits/stdc++.h>
#define int long long
using namespace std;

const int inf = 2e18;
const int N = 3e5 + 1;
const int K = 20;

// floored division
int floor(int a, int b) { return a / b - ((a ^ b) < 0 && a % b); }

// piecewise function
struct F {
    int m, b, lb; // must be strictly greater than lb
    int operator()(int x) { return x > lb ? m * x + b : -inf; }
    F operator+(const F &o) const {
        return {o.m * m, o.b + o.m * b, max(lb, floor(o.lb - b, m))};
    }
} fn[N][K];

int n, h[N], d[N], take[N], dead[N], fa[N][K];

signed main() {
    int m; cin >> n >> m;
    // take input
    for (int i = 1; i <= n; i++) cin >> h[i];
    d[1] = 1;
    for (int i = 2; i <= n; i++) {
        cin >> fa[i][0];
        d[i] = d[fa[i][0]] + 1;
        int t, x; cin >> t >> x;
        if (!t) fn[i][0] = {1, x, --h[i]};
        else fn[i][0] = {x, 0, --h[i]};
    }
    fn[1][0] = {1, 0, --h[1]};
    fn[0][0] = {1, 0, -inf};
    // binary lift
    for (int i = 0; i <= n; i++) {
        for (int k = 0; k < K - 1; k++) {
            fa[i][k + 1] = fa[fa[i][k]][k];
            fn[i][k + 1] = fn[i][k] + fn[fa[i][k]][k];
        }
    }
    for (int i = 0; i < m; i++) {
        int s, c; cin >> s >> c;
        take[i] = d[c];
        F f = fn[c][0];
        int j = 0;
        if (s > f.lb) {
            c = fa[c][0], j = 1;
            for (int k = K; k --> 0; ) {
                if (s > (f + fn[c][k]).lb) {
                    f = f + fn[c][k];
                    c = fa[c][k];
                    j += 1 << k;
                }
            }
        }
        ++dead[c];
        take[i] = min(take[i], j);
    }
    for (int i = 1; i <= n; i++) cout << dead[i] << endl;
    for (int i = 0; i < m; i++) cout << take[i] << endl;
}
