// https://codeforces.com/problemset/problem/1610/I
#include <iostream>
#include <vector>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 3e5 + 1;

int n, nim[N], p[N], v[N];
vector<int> g[N];

void dfs(int x, int p) {
  ::p[x] = p;
  for (int y : g[x]) if (y != p) {
    dfs(y, x); nim[x] ^= nim[y] + 1;
  }
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1, 0);
  int r = nim[1]; v[1] = true;
  cout << (r ? 1 : 2);
  for (int i = 2; i <= n; i++) {
    int j = i;
    while (!v[j]) {
      r ^= 1 ^ nim[j] ^ (nim[j] + 1);
      v[j] = true;
      j = p[j]; 
    }
    cout << (r ? 1 : 2);
  }
  cout << endl;
}
