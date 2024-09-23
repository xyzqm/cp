// https://open.kattis.com/problems/bingoforthewin
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
using namespace std;
map<int, int> c;
map<int, pair<int, int>> l;

const int K = 1e3 + 1;
int a[K][K];

int main() {
  int n, k; cin >> n >> k;
  for (int i = 0; i < n; i++) for (int j = 0; j < k; j++) {
    cin >> a[i][j];
    l[a[i][j]] = {i, j};
    ++c[a[i][j]];
  }
  for (int i = 0; i < n; i++) {
    int t = 0;
    for (int j = 0; j < k; j++) {
      if (l[a[i][j]] == make_pair(i, j)) t += c[a[i][j]];
    }
    cout << fixed << setprecision(8) << (double)t / (n * k) << endl;
  }
}
