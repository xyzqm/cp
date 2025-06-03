// https://codeforces.com/contest/533/problem/F
#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 1;

int prv[256], a[N], z[N], mp[26];

// treat 0 as wildcard
inline bool eq(int x, int y) { return y >= 0 && (!x || x == y); }

int main() {
    int n, m; cin >> n >> m;
    string s, t; cin >> s >> t;
    t += "#" + s;

    // encode string by distance to prv
    vector<int> f; // pos of first oc of each letter in t
    fill(prv, prv + 256, -1);
    for (int i = 0, j = 1; i < t.size(); i++) {
        if (t[i] == '#') {
            fill(prv, prv + 256, -1);
            j = 0, a[i] = -1;
            continue;
        }
        if (prv[t[i]] < 0) { if (j) f.push_back(i); }
        else a[i] = i - prv[t[i]];
        prv[t[i]] = i;
    }

    // compute z-function
    int l = 0, r = 0;
    vector<int> ans;
    for (int i = 1; i < t.size(); i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < t.size() && z[i] < m && eq(a[z[i]], a[i + z[i]])) ++z[i];
        if (i && i + z[i] > r) tie(l, r) = make_pair(i, i + z[i]);
        if (z[i] == m) {
            fill(mp, mp + 26, 0);
            bool w = 1;
            for (int j : f) {
                if (!mp[t[j] - 'a']) mp[t[j] - 'a'] = t[i + j];
                if (!mp[t[i + j] - 'a']) mp[t[i + j] - 'a'] = t[j];
                w &= mp[t[j] - 'a'] == t[i + j] && mp[t[i + j] - 'a'] == t[j];
                w &= a[i + j] > j || !a[i + j];
            }
            if (w) ans.push_back(i - m);
        }
    }
    cout << ans.size() << endl;
    for (int x : ans) cout << x << " ";
    cout << endl;
}
