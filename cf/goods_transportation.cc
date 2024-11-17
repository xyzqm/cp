// https://codeforces.com/problemset/problem/724/E
#include <algorithm>
#include <iostream>
#define int long long
using namespace std;
const int inf = 1e18;

const int N = 2e4;

int n, c, p[N], s[N], D[N], P[N];

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n >> c;
  for (int i = 0; i < n; i++) cin >> p[i];
  for (int i = 0; i < n; i++) cin >> s[i];
  D[0] = p[0], D[1] = s[0];
  for (int i = 1; i < n; i++) {
    P[0] = p[i] + D[0];
    for (int j = 1; j <= i; j++) {
      P[j] = min(c * j + p[i] + D[j], s[i] + D[j - 1]);
    }
    P[i + 1] = s[i] + D[i];
    for (int j = 0; j <= n; j++) swap(D[j], P[j]);
  }
  int r = inf;
  for (int i = 0; i <= n; i++) r = min(r, D[i]);
  cout << r << endl;
}
