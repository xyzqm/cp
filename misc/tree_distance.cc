// https://qoj.ac/contest/1053/problem/5148
#define LCA
#define CENTROID
#include "graph.h"
#include "sgt.h"
using namespace std;

const int N = 2e5 + 1;

struct P { int i; ll d; };
struct E { int u, v; ll w;
  bool operator<(const E &o) const {
    return v == o.v ? w > o.w : v < o.v;
  }
};
vector<P> v[N];
SGT<2 * N, ll> sgt;
ll r[10 * N];
Tree<N, W> t;

int main() {
  int n; cin >> n;
  t.init(n).input().root(1).dfs().decompose();
  for (int i = 1; i <= n; i++) {
    int j = i;
    while (j) {
      v[j].push_back({i, t.D(i, j)});
      j = t.cp[j];
    }
  }
  vector<E> e;
  for (int i = 1; i <= n; i++) {
    vector<P> st;
    for (auto [j, d] : v[i]) {
      while (st.size() && st.back().d >= d) {
        e.push_back({st.back().i, j, st.back().d + d});
        st.pop_back();
      }
      if (st.size()) e.push_back({st.back().i, j, st.back().d + d});
      st.push_back({j, d});
    }
  }
  sgt.fn([](ll x, ll y) { return min(x, y); }, false, inf).fill(inf);
  int q; cin >> q;
  for (int i = 0; i < q; i++) {
    r[i] = inf;
    int u, v; cin >> u >> v;
    e.push_back({u, v, -i});
  }
  sort(e.begin(), e.end());
  for (auto [u, v, w] : e) {
    if (w < 1) r[-w] = sgt.query(u, v);
    else sgt.upd(u, w);
  }
  for (int i = 0; i < q; i++) {
    cout << (r[i] < inf ? r[i] : -1) << endl;
  }
}
