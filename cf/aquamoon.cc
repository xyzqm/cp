// https://codeforces.com/contest/1545/problem/B
#include <iostream>
#include <string>
#define int long long
using namespace std;

const int M = 998244353;

int E(int x, int y) {
  int r = 1;
  for (y <<= 1; y >>= 1; x = x * x % M) if (y & 1) r = r * x % M;
  return r;
}

signed main() {
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    string s; cin >> s;
    int z = 0, o = 0, c = 0;
    for (char h : s) {
      if (h == '0') ++z, o += c / 2, c = 0;
      else ++c;
    }
    o += c / 2;
    int r = 1;
    for (int i = o + z; i > o; i--) r = r * i % M;
    for (int i = 1; i <= z; i++) r = r * E(i, M - 2) % M;
    cout << r << endl;
  }
}
