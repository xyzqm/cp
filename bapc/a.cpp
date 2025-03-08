#include <bits/stdc++.h>
#define int int64_t
using namespace std;

int32_t main() {
  int t; cin >> t;
  while (t--) {
    int a, b, n, m; cin >> a >> b >> n >> m;
    int s = 0;
    while (a < b && a < n) {
      s += a * b;
      a++;
    }
    while (b < a && b < m) {
      s += a * b;
      b++;
    }
    while (a + 1 <= n && b + 1 <= m) {
      s += a * b;
      a++;
      s += a * b;
      b++;
    }
    if (a == n) {
      while (b <= m) s += a * b, b++;
    }
    if (b == m) {
      while (a <= n) s += a * b, a++;
    }
    cout << s << endl;
  }
}