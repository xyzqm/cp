#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
const int N = 1e3 + 1;
const int M = 1e9 + 7;
ll dp[21][N], fact[N], inv[N];
ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % M, --b;
        else b /= 2, a = a * a % M;
    }
    return res;
}
ll c(int n, int k) { return fact[n] * inv[k] % M * inv[n - k] % M; }
int main() {
    fact[0] = inv[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % M;
        inv[i] = pw(fact[i], M - 2);
    }
    int n, K;
    cin >> n >> K;
    dp[0][0] = 1;
    int a;
    for (int i = 1; i <= K; i++) {
        cin >> a;
        for (int j = 0; j <= n; j++) { // number of final red cookies
            for (int k = 0; k <= min(a, j); k++) { // number of new red cookies
                ll red = dp[i - 1][j - k] * c(n - j + k, k) % M; // choose the k new red cookies
                ll rest = c(n - k, a - k);
                dp[i][j] = (dp[i][j] + red * rest) % M;
            }
        }
    }
    cout << dp[K][n] << endl;
}