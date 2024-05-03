#include <iostream>
#define int long long
using namespace std;

const int M = 1e9 + 7;
int E(int x, int y) {
    int r = 1;
    for (y <<= 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x % M;
    return r;
}

int inv(int x) { return E(x, M - 2); }

const int N = 5e3 + 1;
int n, m, a[N], r[N];

signed main() {
    cin >> n >> m;
    int P = 1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        P = P * a[i] % M;
    }
    r[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j > 0; j--) {
            r[j] = r[j] * a[i] % M;
            r[j] -= r[j - 1];
            if (r[j] < 0) r[j] += M;
        }
        r[0] = r[0] * a[i] % M;
       // for (int i = 0; i <= n; i++) cout << r[i] << " ";
       // cout << endl;
    }
    int R = 0, np = 1, mf = 1;
    for (int i = 0; i <= n; i++) {
        R += mf * inv(np) % M * r[i] % M;
        R %= M;
        mf = mf * (m - i) % M;
        np = np * n % M;
    }
    P -= R; if (P < 0) P += M;
    cout << P << endl;
}