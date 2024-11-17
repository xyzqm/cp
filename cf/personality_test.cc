// https://codeforces.com/problemset/problem/1938/G
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define int long long
using namespace std;

const int inf = 1e18;

const int N = 5e3 + 1;
const int M = 3e3 + 1;
const int K = 26;
vector<int> oc[K][M];
int n, m, k, c[N][N];
string s[N];

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) {
    cin >> s[i];
    vector<int> o;
    for (int j = 0; j < m; j++) if (s[i][j] != '.') {
      for (int h : oc[s[i][j] - 'A'][j]) o.push_back(h);
      oc[s[i][j] - 'A'][j].push_back(i);
    }
    sort(o.begin(), o.end(), greater<int>());
    for (int j : o) if (++c[j][i] >= k) { cout << ++j << " " << ++i << endl; return 0; }
  }
  cout << -1 << endl;
}
