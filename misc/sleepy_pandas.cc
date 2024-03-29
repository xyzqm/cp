#include <cmath>
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

const int N = 1e5;
const int K = 11;

int n, k;
ll a[N];
map<int, int> mod[K];

int digits(ll x) { return (int) log10(x) + 1; }

ll tens(int x) {
  ll r = 1;
  while (x--) r = (r * 10) % k;
  return r;
}

int main() {
  int t; cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 0; i < K; i++) mod[i].clear();
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      ++mod[digits(a[i])][a[i] % k];
    }
    ll r = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < K; j++) {
        r += mod[j][(k - (a[i] * tens(j) % k)) % k];
      }
    }
    for (int i = 0; i < n; i++) if ((a[i] * tens(digits(a[i])) + a[i]) % k == 0) --r;
    cout << r << "\n";
  }
}
