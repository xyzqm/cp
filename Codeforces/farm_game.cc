// https://codeforces.com/problemset/problem/1942/E
#include <iostream>
#define int long long
using namespace std;

const int inf = 1e18;

const int N = 1e6 + 2;
const int M = 998244353;
int E(int x, int y) {
  int r = 1;
  for (y <<= 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x % M;
  return r;
}
int inv(int x) { return E(x, M - 2); }
int sb(int x, int y) { return ((x - y) % M + M) % M; }

int F[N];
void pre(int n) { F[0] = 1; for (int i = 1; i < n; i++) F[i] = F[i - 1] * i % M; }
int C(int n, int k) { return F[n] * inv(F[n - k]) % M * inv(F[k]) % M; }

signed main() {
  pre(N);

  cin.tie(0)->sync_with_stdio(0); 
  int t; cin >> t;
  while (t--) {
    int l, n; cin >> l >> n;
    int r = C(l, 2 * n); // total # of possible arrangements
    for (int x = n + 1; x <= l; x++) {
      int k = l - x + 1 + n;
      if (k % 2 != 0 || k / 2 < n - 1) continue;
      r = sb(r, C(x - 1, n) * C(k / 2 - 1, n - 1) % M);
    }
    cout << r * 2 % M << endl;
  }
}
