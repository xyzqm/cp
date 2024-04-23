// https://codeforces.com/problemset/problem/622/F
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

int ne(int x) { return M - x; }

signed main() {
  int n, k; cin >> n >> k;
  ++k;
  int S = 0, N = 1, D = 1, f = 0;
  if (n <= k) {
    for (int i = 1; i <= n; i++) f = (f + E(i, k - 1)) % M;
    cout << f << "\n";
  } else if (k == 1) {
    cout << n << "\n";
  } else {
    for (int i = 0; i <= k; i++) N = N * (n - i) % M;
    for (int i = 1; i <= k; i++) D = D * ne(i) % M;
    for (int i = 0; i <= k; i++) {
      S = (S + E(i, k - 1)) % M;
      // cout << S << " " << N << " " << D << endl;
      f = (f + S * N % M * inv(n - i) % M * inv(D) % M) % M;
      D = ne(D * (i + 1) % M * inv(k - i) % M);
    }
    cout << f << "\n";
  }
}
