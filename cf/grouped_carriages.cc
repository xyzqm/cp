// https://codeforces.com/problemset/problem/1866/G
#pragma GCC optimize("O3,unroll-loops")
#include <iostream>
#include <queue>
#include <vector>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 2e5 + 1;

int n, a[N], d[N];
vector<int> e[N];

bool ck(int v) {
  priority_queue<P, vector<P>, greater<P>> s;
  for (int i = 0; i < n; i++) {
    if (s.size() && s.top().first < i) return false;
    for (int j : e[i]) s.push({j + d[j], a[j]});
    int x = 0;
    while (x < v && s.size()) {
      auto z = s.top(); s.pop();
      if (z.second <= v - x) x += z.second;
      else s.push({z.first, z.second - (v - x)}), x = v;
    }
  }
  return !s.size();
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> d[i];
  for (int i = 0; i < n; i++) if (a[i]) e[max(0LL, i - d[i])].push_back(i);
  int x = 1e9;
  for (int dif = x; dif > 0; dif /= 2) {
    while (x - dif >= 0 && ck(x - dif)) x -= dif;
  }
  cout << x << endl;
}
