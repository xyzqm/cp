#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
#define int long long
const int inf = 1e18;
using T = tuple<int, int, int>;
const int A = 1e6 + 1;
const int M = 1e9 + 7;
const int N = 1e5;
int n, F[A], I[A], a[N];
int P(int x, int y) {
    int r = 1;
    for (y <<= 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x % M;
    return r;
}
int C(int n, int k) { return F[n] * I[n - k] % M * I[k] % M; }
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    F[0] = I[0] = 1;
    for (int i = 1; i < A; i++) F[i] = F[i - 1] * i % M, I[i] = P(F[i], M - 2);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i], a[i] /= 2;
    int r = 1;
    for (int i = n - 1; i --> 0; ) {
        if (a[i] > a[i + 1]) r = r * C(a[i], a[i + 1]) % M;
        else r = r * C(a[i + 1] - 1, a[i] - 1) % M;
    }
    cout << r << endl;
    return 0;
}