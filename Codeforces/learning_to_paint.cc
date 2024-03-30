/**
https://codeforces.com/contest/1942/problem/D

Solution sketch:
dp[i] = max k values while only painting first i elements
for all i: (N)
  let s[-1] = dp[i - 1] (1)
  for all j <= i: (N)
    let s[j] = dp[j - 1] + a[j, i]
  sort s by max value in decreasing order
  insert until we have k elements

Overall complexity: N^2 log n
*/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int N = 1e3 + 1;

int n, a[N][N];
vector<int> dp[N];

struct S {
  int x, j, i;
  int v() const { return x + (j >= 0 ? dp[j][i] : 0); }
  S next() const { return {x, j, i + 1}; }
  bool operator<(const S& o) const { return v() > o.v(); }
};

int main() {
  dp[0] = {0};
  int t; cin >> t;
  while (t--) {
    int k; cin >> n >> k;

    for (int i = 1; i <= n; i++) dp[i].clear();
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j++) cin >> a[i - 1][j]; // non-inclusive
    }

    for (int i = 1; i <= n; i++) {
      multiset<S> s;
      for (int j = 0; j <= i; j++) s.insert({a[j][i], j - 1, 0});
      while (s.size() && dp[i].size() < k) {
        auto it = s.begin();
        dp[i].push_back(it->v());
        if (it->i + 1 < dp[it->j].size()) s.insert(it->next());
        s.erase(it);
      }
    }
    for (int x : dp[n]) cout << x << " ";
    cout << endl;
  }
}
