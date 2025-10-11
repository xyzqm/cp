#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 2e5 + 1;
const int M = 998244353;

int inv(int x) {
    int r = 1;
    for (int p = (M - 2) * 2; p >>= 1; x = x * x % M) if (p & 1) r = r * x % M;
    return r;
}

int F[N], I[N];

int C(int n, int k) { return n >= k ? F[n] * I[n - k] % M * I[k] % M : 0; }

void ac() {
    int n, m; cin >> n >> m;
    vector<int> a(n * m);
    for (int &x : a) cin >> x;
    sort(a.begin(), a.end());
    a.insert(a.begin(), 0);
    int r = 0;
    for (auto it = ++a.begin(); it != a.end(); it++) {
        int x = it - a.begin();
        for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) if (i || j) {
            int mul = (((i + j) & 1) ? 1 : M - 1);
            int rem = x - i * m - n * j + i * j;
            if (rem >= 0) r = (r + mul * C(n, i) % M * C(m, j) % M * C((n - i) * (m - j), rem) % M * F[x] % M * F[n * m - x] % M * (*it - *prev(it)) % M);
        }
    }
    cout << r << endl;
}

int32_t main() {
    // precompute factorials and inverse factorials
    F[0] = 1;
    for (int i = 1; i < N; i++) F[i] = F[i - 1] * i % M;
    I[N - 1] = inv(F[N - 1]);
    for (int i = N; i --> 1; ) I[i - 1] = I[i] * i % M;
    int t; cin >> t;
    while (t--) ac();
}
