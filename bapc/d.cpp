#include <bits/stdc++.h>
//#define int64_t
using namespace std;

void solve() {
  int n,m;
  cin >> n >> m;

  vector<vector<int>> enths(n);
  for (int i = 0;i<n;i++) {
    int curSs;
    cin >> curSs;
    enths[i] = vector<int>(curSs);
    for (int j =0;j<curSs;j++){
      cin >> enths[i][j];
    }
    sort(enths[i].begin(),enths[i].end());
  }

  vector<vector<int>> ends(n);
  for (int i=0;i<m;i++) {
    int l,r;
    cin >> l>>r;
    l--;r--;
    ends[l].push_back(r);
  }

  multiset<int> curEnds;
  for (int i = 0;i<n;i++){
    for (auto ev : ends[i]) {
      curEnds.insert(ev);
    }

    while (!curEnds.empty() && (*curEnds.begin()) < i) {
      curEnds.erase(curEnds.begin());
    }

    for (int j = 0;j<enths[i].size();j++){
      if (enths[i][j] <= j) {
        cout << "NO\n";
        return;
      }
    }

    if (enths[i].size() > curEnds.size()) {
      cout << "NO\n";
      return;
    }

    for (int j= 0;j<enths[i].size();j++){
      if (curEnds.empty()) {
        cout << "NO\n";
        return;
      }
      auto it = curEnds.end();
      it--;
      curEnds.erase(it);
    }
  }
  cout << "YES\n";
}

int32_t main() {
  int t;
  cin >> t;
  for (int i=0;i<t;i++){
    solve();
  }
}