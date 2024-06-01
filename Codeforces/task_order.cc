// https://codeforces.com/problemset/problem/1918/E
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <chrono>
#define int long long
using namespace std;
using P = pair<int, int>;
const int inf = 1e18;

const int N = 2e3 + 1;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
string q(int i) {
  cout << "? " << i << endl;
  string s; cin >> s;
  return s;
}

vector<int> sort(vector<int> v) {
  if (v.size() < 2) return v;
  int _ = rng() % v.size();
  int i = v[_];
  while (q(i) != "=");
  vector<int> l, r;
  for (int x : v) if (x != i) {
    if (q(x) == "<") l.push_back(x);
    else r.push_back(x);
    q(i);
  }
  l = sort(l), r = sort(r);
  vector<int> R;
  for (int x : l) R.push_back(x);
  R.push_back(i);
  for (int x : r) R.push_back(x);
  return R;
}

void ac() {
  int n; cin >> n;
  vector<int> v(n), r(n + 1);
  iota(v.begin(), v.end(), 1);
  v = sort(v);
  for (int i = 0; i < n; i++) r[v[i]] = i + 1;
  cout << "! ";
  for (int i = 1; i <= n; i++) cout << r[i] << " ";
  cout << endl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); 
  int t; cin >> t;
  while (t--) ac();
}
