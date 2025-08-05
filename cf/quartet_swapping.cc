// https://codeforces.com/contest/2101/problem/B
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int inversions(vector<int>& v) {
    if (v.size() < 2) return 0;
    int m = v.size() >> 1;
    vector<int> l(v.begin(), v.begin() + m);
    vector<int> r(v.begin() + m, v.end());
    int ans = inversions(l) + inversions(r);
    auto L = l.begin(), R = r.begin(), V = v.begin();
    while (L != l.end() && R != r.end()) {
        if (*L < *R) *V = *(L++), ans += R - r.begin();
        else *V = *(R++);
        ++V;
    }
    copy(L, l.end(), V);
    ans += (l.end() - L) * r.size();
    copy(R, r.end(), V);
    return ans;
}

void ac() {
    int n; cin >> n;
    array<vector<int>, 2> s;
    vector<int> v(n), idx(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        s[i % 2].push_back(v[i]);
        idx[v[i]] = i;
    }
    bool bad = inversions(s[0]) % 2 != inversions(s[1]) % 2;
    for (int t : {0, 1}) for (int i = t, j = 0; i < n; i += 2, ++j) v[i] = s[t][j];
    if (bad) swap(v[v.size() - 3], v.back());
    for (int x : v) cout << x << " ";
    cout << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
