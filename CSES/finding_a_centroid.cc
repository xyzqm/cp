#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 1;
int n, s[N];
vector<int> g[N];

int sz(int x = 1, int p = 0) {
  for (int y : g[x]) if (y != p) s[x] += sz(y, x);
  return ++s[x];
}

int dfs(int x = 1, int p = 0) {
  for (int y : g[x]) if (y != p) {
    if (s[y] > n / 2) return dfs(y, x);
  }
  return x;
}

int main() {
  cin >> n;
  for (int i = 1; i < n; i++) {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  sz();
  cout << dfs() << endl;
}
