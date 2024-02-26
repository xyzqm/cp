#include <iostream>
using namespace std;
#define int long long
const int inf = 1e18;
const int N = 1e5 + 1;
const int K = 1e9;
int t, b, n, p[N], L[N], R[N], l[N], r[N], s[N];
bool ck(int k) {
    for (int i = 1; i <= n; i++) l[i] = L[i] - k, r[i] = R[i] + k;
    for (int i = n; i > 0; i--) {
        if (l[i] > r[i] || r[i] < l[i]) return false;
        if (p[i] && (l[i] > R[p[i]] || r[i] < L[p[i]])) return false;
        l[p[i]] = max(l[p[i]], l[i]);
        r[p[i]] = min(r[p[i]], r[i]);
    }
    return true;
}
void sl(int k) {
    ck(k);
    for (int i = 0; i <= n; i++) {
        L[p[i]] = max(L[p[i]], l[i]);
        R[p[i]] = min(R[p[i]], r[i]);
        l[i] = 0, r[i] = inf;
    }
    for (int i = 1; i <= n; i++) {
        s[i] = max(L[i], l[p[i]]);
        l[i] = max(l[p[i]], s[i] - k);
        r[i] = min(r[p[i]], s[i] + k);

    }
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> t >> b;
    while (t--) {
        cin >> n;
        for (int i = 2; i <= n; i++) cin >> p[i];
        for (int i = 1; i <= n; i++) cin >> L[i] >> R[i];
        int x = -1;
        for (int d = K; d > 0; d /= 2) while (x + d < K && !ck(x + d)) x += d;
        cout << x + 1 << endl;
        if (b) {
            sl(x + 1);
            for (int i = 1; i <= n; i++) cout << s[i] << " \n"[i == n];
        }
    }
    return 0;
}