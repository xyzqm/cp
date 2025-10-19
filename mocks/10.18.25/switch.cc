#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int M = 998244353;
const int N = 1e7 + 1;

int inv[N];

int32_t main() {
    int n; cin >> n;
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = M - M / i * inv[M % i] % M;
    int r = 2 * n % M;
    for (int i = 1; i <= n; i++) {
         r -= inv[i];
         if (r < 0) r += M;
    }
    cout << r << endl;
}
