/**
Solution sketch:
A given node i will contribute to the answer for
nCk - sum[subtreeCk] - othersCk subsets
cnt_i --- the number of times the term iCk appears
Then the answer for k is n*nCk - sum[cnt_i * iCk]
sum[cnt_i * iCk] = 1/k! * sum[(cnt_i * i!)/(i - k)!]
1/k! is constant for each k, and (n - i) + (i - k) = n - k
Thus if a_i = cnt_i * i! and b_i = 1/i!
test
ANS_reversed = n*nCk - 1/k! * convolute(a_reversed, b)
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#define int long long
using namespace std;

// ---MODS---
const int N = 2e5 + 1;
const int M = 924844033;
const int W = 5;

int F[N];

int E(int x, int y) {
  int r = 1;
  for (y <<= 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x % M;
  return r;
}

void fact(int n) {
  F[0] = 1;
  for (int i = 1; i <= n; i++) F[i] = F[i - 1] * i % M;
}

int inv(int x) { return E(x, M - 2); }

int C(int n, int k) { return F[n] * inv(F[k]) % M * inv(F[n - k]) % M; }

// ---FFT---
// evaluates the polynomial sum(a[i] * x^i) at w^[0...n - 1]
template <typename T>
vector<T> fft(vector<T> a, T w) {
  if (a.size() == 1) return a;
  int n = a.size();
  vector<T> e(n / 2), o(n / 2);
  for (int i = 0; i < a.size(); i++) {
    (i % 2 ? o : e)[i / 2] = a[i];
  }
  vector<T> E = fft(e, w * w % M);
  vector<T> O = fft(o, w * w % M);
  vector<T> r(n);
  T c = 1;
  for (int i = 0; i < n; i++) {
    r[i] = (E[i % (n / 2)] + c * O[i % (n / 2)]) % M;
    c = c * w % M;
  }
  return r;
}

// ---TREE---
int n, s[N], c[N];
vector<int> g[N];

void dfs(int x, int p) {
  for (int y : g[x]) if (y != p) {
    dfs(y, x);
    s[x] += s[y];
  }
  ++s[x];
  if (p) ++c[s[x]];
  ++c[n - s[x]];
}

//---MAIN---
signed main() {
  cin >> n;
  fact(n);
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1, 0);
  int k = 1 << (64 - __builtin_clzll(n) + 1);
  vector<int> a(k), b(k);
  for (int i = 1; i <= n; i++) a[n - i] = c[i] * F[i] % M;
  for (int i = 0; i < n; i++) b[i] = inv(F[i]);
  int w = E(W, (M - 1) / k);
  vector<int> A = fft(a, w);
  vector<int> B = fft(b, w);
  vector<int> R(k);
  for (int i = 0; i < k; i++) R[i] = A[i] * B[i] % M;
  vector<int> r = fft(R, inv(w));
  for (int i = 1; i <= n; i++) {
    cout << (n * C(n, i) % M - r[n - i] * inv(k) % M * inv(F[i]) % M + M) % M << endl;
  }
}
