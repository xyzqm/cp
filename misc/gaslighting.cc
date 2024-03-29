// TeamsCode 2024
#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;
const int N = 7000;
const int K = 1e6;

int n, lcp[N][N];

struct P { int i, r; } res[N][N];
struct R { int l, r; } ans[K];
struct Q {
  int l, r, i;
  bool operator<(const Q& o) const {
    return make_pair(l, r) < make_pair(o.l, o.r);
  }
} queries[K];

int main() {
  int q; cin >> n >> q;
  string s; cin >> s;
  for (int i = n; i --> 0; ) {
    for (int j = n; j --> 0; ) {
      if (i == n - 1 || j == n - 1) lcp[i][j] = (s[i] == s[j]);
      else lcp[i][j] = (s[i] == s[j]) * (1 + lcp[i + 1][j + 1]);
      int h = lcp[i][j];
      if (i + h >= n || j + h >= n) continue;
      int k = (max(i, j) + h + 1 < n ? lcp[i + h + 1][j + h + 1] + 1 : 1);
      if (i + h + k > res[i][i + h].r) res[i][i + h] = {j, i + h + k};
    }
  }
  for (int i = 0; i < q; i++) {
    int l, r; cin >> l >> r;
    queries[i] = {--l, --r, i};
    ans[i] = {-1, -1};
  }
  sort(queries, queries + q);
  int qi = 0;
  for (int i = 0; i < n; i++) {
    int cur = -1, r = 0;
    for (int j = i; j < n; j++) {
      if (res[i][j].r > r) {
        cur = res[i][j].i;
        r = res[i][j].r;
      }
      while (qi < q && (queries[qi].l < i || queries[qi].l == i && queries[qi].r < j)) ++qi;
      if (j < r) while (qi < q && queries[qi].l == i && queries[qi].r == j) {
        ans[queries[qi++].i] = {cur, cur + j - i};
      }
    }
  }
  for (int i = 0; i < q; i++) {
    cout << ++ans[i].l << " " << ++ans[i].r << "\n";
  }
}
