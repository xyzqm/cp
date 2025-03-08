#include <bits/stdc++.h>
#define int int64_t
using namespace std;

void ac() {
  int n; cin >> n;
  vector<int> h(n);
  for (int &x : h) cin >> x;
  int r = 0, l = 0;
  for (int i = 0; i + 1 < n; i++) if (h[i] < h[i + 1]) ++r;
  for (int i = 0; i < n; i++) {
    cout << max(l, r) << " ";
    if (i + 1 == n) break;
    if (h[i] > h[i + 1]) ++l;
    if (h[i] < h[i + 1]) --r;
  }
  cout << endl;
}

int32_t main() {
  int t; cin >> t;
  while (t--) ac();
}