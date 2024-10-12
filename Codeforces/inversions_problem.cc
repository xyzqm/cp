// https://codeforces.com/problemset/problem/1917/D
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cassert>
using namespace std;
#define int long long
const int inf = 1e18;
const int N = 4e5;
const int M = 998244353;
const int I = (M + 1) / 2;
int n, k, U, K, p[N], q[N];
struct BIT {
    int a[N + 1]{};
    void upd(int i, int x) {
        // cout << i << endl;
        i = U - i;
        for (; i <= U; i += i & -i) a[i] = (a[i] + x) % M;
    }
    int qry(int i) {
        // cout << i << endl;
        i = U - i;
        assert(i > 0);
        int r = 0;
        for (; i; i -= i & -i) r = (r + a[i]) % M;
        return r;
    }
    void clear() { fill(a, a + U + 1, 0); }
};
int T(int n) { return n * (n + 1) % M * I % M; }
BIT b, c;
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> k;
        U = max(2 * n, k);
        for (int i = 0; i < n; i++) cin >> p[i];
        for (int i = 0; i < k; i++) cin >> q[i];
        b.clear();
        int qinv = 0;
        for (int i = 0; i < k; i++) {
            qinv += b.qry(q[i]);
            b.upd(q[i], 1);
        }
        qinv %= M;
        b.clear(), c.clear();
        int r = qinv * n % M;
        int g = 0;
        for (int i = 0; i < n; i++) {
            int x = p[i];
            r = (g + r + b.qry(x)) % M;
            int l = 0;
            for (int j = 0; j < k && x < 2 * n; j++) {
                b.upd(x, k - j);
                l = j;
                if ((x <<= 1) < 2 * n) r = (r + c.qry(x) * (k - 1 - j) % M) % M;
            }
            c.upd(p[i], 1);
            if (x >= 2 * n) g = (g + T(k - l - 1)) % M;
        }
        cout << r << "\n";
    }
    return 0;
}