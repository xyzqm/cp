// https://open.kattis.com/contests/n2jtkf/problems/sunandmoon
#include <iostream>
#include <map>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 1e5 + 1;

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  map<int, bool> m;
  int a, b, c, d; cin >> a >> b >> c >> d;
  a = -a;
  while (a <= 5000) {
    if ((a += b) > 0) m[a] = true;
  }
  c = -c;
  while (c <= 5000) {
    if (m[c += d]) { cout << c << endl; return 0; }
  }
}
