#include <iostream>
using namespace std;

const int N = 7e5 + 1;
const int inf = 1e9;

int n, a[N], pre[N], suf[N];

int main() {
  int t; cin >> t;
  while (t--) {
    int q; cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    a[0] = inf;
    pre[1] = 1, suf[n] = n;
    for (int i = 2; i <= n; i++) {
      if (a[i] > a[pre[i - 1]]) pre[i] = i;
      else if (a[i] < a[pre[i - 1]]) pre[i] = pre[i - 1];
      else pre[i] = 0;
    }
    for (int i = n; i --> 1; ) {
      int next = (i + 2 <= n ? a[suf[i + 2]] : -inf);
      if (a[i] > a[i + 1]) suf[i] = (a[i] > next ? i : suf[i + 2]);
      if (a[i] < a[i + 1]) suf[i] = suf[i + 1];
    }
  }
}
