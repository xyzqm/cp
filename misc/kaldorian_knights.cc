#include <iostream>
using namespace std;
using ll = long long;
const int N = 1e6 + 1;
const int M = 1e9 + 7;
const int H = 5e3;
ll n, F[N], res[H];
int h, k[H], pre[H];
int main() {
    // preprocessing
    F[0] = 1;
    for (int i = 1; i < N; i++) F[i] = F[i - 1] * i % M;
    // end preprocessing
    cin >> n >> h;
    for (int i = 0; i < h; i++) {
        cin >> k[i];
        pre[i] = k[i] + (i ? pre[i - 1] : 0);
    }
    ll ans = F[n];
    for (int i = 0; i < h; i++) {
        res[i] = F[pre[i]] % M;
        for (int j = 0; j < i; j++) {
            res[i] -= res[j] * F[pre[i] - pre[j]] % M;
        }
        res[i] %= M;
        if (res[i] < 0) res[i] += M;
        ans -= res[i] * F[n - pre[i]] % M;
        ans %= M;
        if (ans < 0) ans += M;
    }
    cout << ans << endl;
}