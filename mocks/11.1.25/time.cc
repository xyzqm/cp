#include <bits/stdc++.h>
using namespace std;

#define int int64_t
const int M = 998244353;

int inv(int x) {
    int r = 1;
    for (int e = M - 2; e; e >>= 1, x = x * x % M) if (e & 1) r = r * x % M;
    return r;
}

void ad(int &x, int y) { x = (x + y) % M; }
void sb(int &x, int y) {
    x -= y % M;
    if (x < 0) x += M;
}

int32_t main() {
    int n; cin >> n;
    int sm = 0;
    for (int i = 0, x = 0; i < n && cin >> x; i++) ad(sm, x);
    int iv = inv(n);
    int mul = (n - 1) * iv % M, ans = 2 * sm, tot = sm * mul % M;
    sm = sm * iv % M;
    for (int i = 2 * n, x = 0; i --> n && cin >> x; ) {
        sm = sm * mul % M;
        ad(sm, iv * x % M);
        ad(ans, i * sm);
        ad(tot, x);
        sb(tot, sm);
    }
    ad(ans, tot * n % M * ((M + 1) / 2) % M);
    cout << ans << endl;
}
