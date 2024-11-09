#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5 + 1;
int n, m, A, B, C, t[N], b[N];
__int128 ck(int mx) {
    int a1 = 0, a2 = 0, r = 0;
    for (int i = 0; i < n; i++) r += max(mx - t[i], 0LL);
    for (int i = 0; i < m; i++) {
        if (b[i] < mx) a1 += mx - b[i];
        else a2 += b[i] - mx;
    }
    int a = (A < B ? min(a1, a2) : 0);
    // cout << mx << " " << r << " " << a << " " << a2 << endl;
    return __int128(r) * C + a * A + (a2 - a) * B;
}

signed main() {
    cin >> A >> B >> C >> n >> m;
    for (int i = 0; i < n; i++) cin >> t[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    int x = 0;
    for (int d = 1 << 20; d >>= 1; ) {
        if (ck(x + d) < ck(x + d - 1)) x += d;
    }
    cout << (int)ck(x) << endl;
}
