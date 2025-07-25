// https://atcoder.jp/contests/arc067/tasks/arc067_d
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int N = 5e3 + 1;
const int M = 201;
const int K = 13;
int n, m, a[N];

int smax(int &a, int b) { return a = max(a, b); }
struct ST : array<array<int, N>, K> {
    void build() {
        for (int k = 0; k < K - 1; k++) {
            at(k + 1) = at(k);
            for (int i = 0; i < n - (1 << k); i++) {
                smax(at(k + 1).at(i), at(k).at(i + (1 << k)));
            }
        }
    }

    int query(int l, int r) {
        int k = __lg(r - l);
        return max(at(k).at(l), at(k).at(r - (1 << k)));
    }
} b[M];

// left endpoint for i is in range [l, r]
int solve(int x, int y, int l, int r) {
    if (x == y) return 0;
    int i = (x + y) / 2;
    pair<int, int> opt = {0, i};
    for (int j = min(i, r); j >= l; j--) {
       int s = a[j] - a[i];
       for (int k = 0; k < m; k++) s += b[k].query(j, i + 1);
       opt = max(opt, {s, j});
    }
    if (y - x == 1) return opt.first;
    return max({opt.first, solve(x, i, l, opt.second), solve(i, y, opt.second, r)});
}

int32_t main() {
   cin >> n >> m;
   for (int i = 1; i < n; i++) cin >> a[i];
   partial_sum(a, a + n, a);
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < m; j++) cin >> b[j][0][i];
   }
   for (int i = 0; i < m; i++) b[i].build();
   cout << solve(0, n, 0, n - 1) << endl;
}
