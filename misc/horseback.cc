#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cassert>
#define int long long
using namespace std;

const int N = 3e5 + 1;
int l[N], r[N], o[N];
bool u[N];

struct E {
	int t, i, s; bool add;
	bool operator<(const E &o) const { return t == o.t ? add > o.add : t < o.t; }
};

set<pair<int, int>> S[2]; 

signed main() {
	int n, s; cin >> n >> s;
	vector<E> v;
	for (int i = 0; i < n; i++) {
		cin >> l[i] >> r[i];
		r[i] = min(s - 1, r[i]);
		if (l[i] > r[i]) continue;
		if (l[i] < (s + 1) / 2) {
			v.push_back({l[i], i, 0, true});
			if (r[i] < (s + 1) / 2) v.push_back({o[i] = r[i], i, 0, false});
		}
		if (r[i] > s / 2) {
			v.push_back({s - r[i], i, 1, true});
			if (l[i] > s / 2) v.push_back({o[i] = s - l[i], i, 1, false});
		}
		if (!o[i]) o[i] = (s + 1) / 2;
	}
	sort(v.begin(), v.end());
	vector<pair<int, int>> R;
	for (auto [t, i, j, add] : v) {
		assert(t < (s + 1) / 2);
		if (add && !u[i]) S[j].insert({o[i], i});
		else {
			while (S[!j].size() && u[S[!j].begin()->second]) S[!j].erase(S[!j].begin());
			if (!u[i] && S[!j].size()) {
				auto it = S[!j].begin();
				assert(it->first >= t);
				R.push_back({i, it->second});
				u[i] = u[it->second] = true;
				S[!j].erase(it);
			}
			assert(S[!j].find({o[i], i}) == S[!j].end());
			if (S[j].find({o[i], i}) != S[j].end()) S[j].erase({o[i], i});
		}
	}
	vector<int> rem;
	for (int i = 0; i < n; i++) if (2 * l[i] <= s && 2 * r[i] >= s && !u[i]) rem.push_back(i);
	for (int i = 0; i < (int)rem.size() - 1; i += 2) {
    R.push_back({rem[i], rem[i + 1]});
  }
	
	cout << R.size() << endl;
	for (auto [x, y] : R) cout << ++x << " " << ++y << endl;
}

