#include "mint.h"
#include "combo.h"
using namespace std;

const int N = 2e5 + 1;
const int M = 998244353;

Combo<N, M> C;

int main() {
  int n, m; cin >> n >> m;
  if (n < m) { cout << 0 << endl; return 0; }
  mint r = mint{0} - C.C(2 * n, n);
  int x = n, y = n, a = 1, b = m + 1, s = 1;
  while (x >= 0 || y >= 0) {
    if (x >= 0) r += C.C(2 * n, x) * s;
    if (y >= 0) r += C.C(2 * n, y) * s;
    x -= a, y -= b, s = -s;
    swap(a, b);
  }
  cout << r << endl;
}
