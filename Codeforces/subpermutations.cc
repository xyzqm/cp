// https://codeforces.com/problemset/problem/1861/E
const int M = 998244353;
const int A = 4e3 + 1;
#include "mint.h"
#include "combo.h"
const int N = 4e3 + 1;
mint c[N], t[N], sm[N], cnt[N];

int main() {
  pre();
  int n, k; cin >> n >> k;
  for (int i = k; i <= n; i++) {
    c[i] = F[k] * (mint{k} ^ (i - k));
    for (int j = k; j < i; j++) {
      c[i] -= c[j] * F[min(i - j, k)] * (mint{k} ^ max(0, i - j - k));
    }
  }
  for (int i = 0; i <= n; i++) {
    t[i] = mint{k} ^ i;
    for (int j = k; j <= i; j++) {
      t[i] -= c[j] * (mint{k} ^ (i - j));
    }
  }
  c[k] = F[k];
  sm[0] = 0, cnt[0] = 1;
  mint r = 0;
  for (int i = k; i <= n; i++) {
    for (int j = 0; j <= i - k; j++) {
      sm[i] += (sm[j] + cnt[j]) * c[i - j];
      cnt[i] += cnt[j] * c[i - j];
    }
    r += sm[i] * t[n - i];
  }
  cout << r << endl;
}

