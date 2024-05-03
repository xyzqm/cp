#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using P = pair<int, int>;
const int N = 1e4;

int n, mn, rx[N], ry[N];
bool vi[N];
vector<P> p;

template <typename T>
T at(vector<T> &v, int i) {
  return v[(i + v.size()) % v.size()];
}

struct V {
  int x, y;
  V(int x, int y) : x(x), y(y) {}
  V(P s, P t) : x(t.first - s.first), y(t.second - s.second) {}
  int norm() { return x * x + y * y; }
  int operator*(V b) { return x * b.y - y * b.x; }
};

vector<int> solve() {
  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());
  vector<int> hull{0};
  P pivot = p[0];
  // sort points by angle to pivot
  sort(p.begin(), p.end(), [&](P x, P y) {
    V a(pivot, x), b(pivot, y);
    if (a * b) return a * b > 0;
    else return a.norm() < b.norm();
  });
  for (int i = 1; i < p.size(); i++) {
    while (hull.size() > 1 && V(p[at(hull, -2)], p[hull.back()]) * V(p[hull.back()], p[i]) <= 0) hull.pop_back();
    hull.push_back(i);
  }
  return hull;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  while (true) {
    cin >> n;
    if (!n) break;
    p.clear();
    for (int i = 0; i < n; i++) {
      int x, y; cin >> x >> y;
      p.push_back({x, y});
    }
    auto ans = solve();
    cout << ans.size() << "\n";
    for (int x : ans) cout << p[x].first << " " << p[x].second << "\n";
  }
}
