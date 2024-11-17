// https://codeforces.com/contest/1938/problem/F
#include <iostream>
#include <numeric>
#include <set>
#define int long long
using namespace std;
const int inf = 1e18;

const int N = 1e6 + 1;

int n, a1, a[N], S[N];

bool np[N];
void sieve() {
  for (int i = 2; i < N; i++) if (!np[i]) {
    for (int j = 2 * i; j < N; j += i) np[j] = true;
  }
}

void ac() {
  cin >> n >> a1;
  for (int i = 1; i < n; i++) cin >> a[i];
  int p = 1, q = 0;
  auto upd = [&](int x, int y) {
    int g = gcd(x, y); x /= g; y /= g;
    if (x * q < p * y) p = x, q = y;
  };
  multiset<int> s;
  auto rem = [&](int x) { s.erase(s.find(x)); };
  for (int i = 2; i <= n; i++) if (n % i == 0 && !np[i]) {
    s.clear();
    for (int j = 0; j < i; j++) S[j] = 0;
    for (int j = 1; j < n; j++) S[j % i] += a[j];
    for (int j = 1; j < i; j++) s.insert(S[j]);
    s.insert(S[0] += a1);
    for (int j = 0; j < n; j++) {
      upd(*s.rbegin(), *s.begin()); 
      if (j == n - 1) break;
      rem(S[j % i]); s.insert(S[j % i] -= a1 - a[j + 1]);
      rem(S[(j + 1) % i]); s.insert(S[(j + 1) % i] += a1 - a[j + 1]);
    }
  }
  cout << p << " " << q << endl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  sieve();
  int t; cin >> t;
  while (t--) ac();
}
