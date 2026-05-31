#include <algorithm>
#include <iostream>
 
using namespace std;
 
const int N = 1000000;
 
char cc[N + 1];
 
int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);
  int n; long long c_; cin >> n >> c_ >> cc;
  long long c = 0;
  for (int k = 0, i = 0; i < n; i++)
    if (cc[i] == '0')
      c += k;
    else
      k++;
  c_ = c - c_;
  int x = 0;
  for (int i = 0, j = n - 1; c_ > 0; ) {
    while (cc[i] != '1')
      i++;
    while (cc[j] != '0')
      j--;
    x++, c_ -= j - i;
  }
  cout << x << '\n';
  return 0;
}