// https://www.acmicpc.net/problem/23199
#include <iostream>
#include <numeric>
#include <vector>
#include <cassert>
using namespace std;

const int N = 1e2 + 1;
vector<int> g[N];

int n;
string test(vector<int> p) {
  assert(p.size() == n + 1);
  cout << "test ";
  for (int i = 1; i <= n; i++) cout << p[i] << " ";
  cout << endl;
  string s; cin >> s; s.insert(s.begin(), '0'); // to 1-index
  return s;
}

// given current groups are v, return final good group
int find(vector<int> v) {
  if (v.size() == 1) return v[0];
  vector<int> p(n + 1);
  for (int i = 0; i < v.size() - 1; i += 2) {
    p[v[i]] = v[i + 1];
    p[v[i + 1]] = v[i];
  }
  string s = test(p);
  vector<int> r;
  for (int i = 1; i <= n; i++) if (p[i] && i < p[i]) {
    if (s[i] == '1' && s[p[i]] == '1') {
      g[i].insert(g[i].end(), g[p[i]].begin(), g[p[i]].end());
      r.push_back(i);
    }
  }
  if (!r.size()) return v.back();
  else return find(r);
}

void ac() {
  cin >> n;
  for (int i = 1; i <= n; i++) g[i] = {i};
  vector<int> v(n); iota(v.begin(), v.end(), 1);
  int r = find(v);
}
