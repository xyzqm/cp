// https://loj.ac/p/2173
#include <iostream>
#define int long long
using namespace std;

const int inf = 1e18;

const int N = 5e4 + 1;
const int M = 1e9 + 7;
const int K = 2e2 + 1;
int v[N][K];

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
  cin.tie(0)->sync_with_stdio(0); 
  pre(N);
  v[0][0] = 1;
  for (int i = 1; i < N; i++) {
    for (int j = 1; j < K; j++) {
      v[i][j] = ((i - 1) * v[i - 1][j] % M + v[i - 1][j - 1]) % M;
    }
  }
  int t; cin >> t;
  while (t--) {
    int n, a, b; cin >> n >> a >> b;
    cout << v[n - 1][a + b - 2] * C(a + b - 2, a - 1) % M << endl;   
  }
}
