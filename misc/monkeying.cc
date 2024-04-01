#include <climits>
#include <iostream>
#include <map>
using namespace std;

const int N = 1e5;

int n, a[N];

int main() {
  int t; cin >> t;
  while (t--) {
    cin >> n;
    int OR = 0, AND = INT_MAX;
    map<int, int> count;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      OR |= a[i], AND &= a[i];
      ++count[a[i]];
    }
    int O = n, A = n;
    for (int i = 0; i < n; i++) {
      if ((a[i] | OR) == a[i]) O = min(O, n - count[a[i]]);
      if ((a[i] & AND) == a[i]) A = min(A, n - count[a[i]]);
    }
    if (O < A) cout << "or\n";
    else if (A < O) cout << "and\n";
    else cout << "sad\n";
  }
}
