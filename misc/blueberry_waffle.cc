// https://open.kattis.com/contests/n2jtkf/problems/blueberrywaffle
#include <iostream>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e5 + 1;

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int r, f; cin >> r >> f;
  int x = (f / r) % 2 - (2 * (f % r) > r);
  cout << (x ? "down" : "up") << endl;
}
