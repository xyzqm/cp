#include <iostream>
using namespace std;
using ll = long long;
using LL = __int128;
const int K = 2e4;
ll c[K], n, T, k;
bool check(LL x) {
    LL tot = 0;
    for (int i = 0; i < k; ++i) {
        LL ring = (x - c[i]) / T + 1;
        if (x < c[i] || ring <= 0) break;
        tot += ring * (ring + 1) * 2;
    }
    return tot >= n;

}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> T >> k;
    for (int i = 0; i < k; i++) cin >> c[i];
    LL C = 8e18;
    for (LL dif = 8e18; dif > 0; dif /= 2) {
        while (C - dif > 0 && check(C - dif)) C -= dif;
    }
    ll p = 0;
    LL ans = 0;
    for (ll i = 0; n; i++) {
        p += 4;
        bool delta = false;
        for (int j = 0; j < k; j++) {
            LL cost = c[j] + i * T;
            if (cost >= C || p > n) break;
            delta = true;
            ans += cost * p;
            n -= p;
        }
        if (!delta) break;
    }
    cout << ll(ans + n * C) << endl;
}