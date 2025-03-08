#include <bits/stdc++.h>
#define int int64_t
using namespace std;

const int N = 1 << 25;

int c[N];

int32_t main() {
  int n, m; cin >> n >> m;
  for (int _ = 0; _ < n; _++) {
    int k = 0;
    for (int i = 0; i < m * m; i++) {
      char c; cin >> c;
      k += (c == 'X') * (1 << i);
    }
    ++c[k];
  }
  int r = c[0] * (n - c[0]);
  for (int i = 0; i < N; i++) {
    r += c[i] * (c[i] - 1) / 2;
  }
  cout << r << endl;
}