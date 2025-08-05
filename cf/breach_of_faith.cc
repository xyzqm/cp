#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void ac() {
    int n; cin >> n;
    vector<int> v(2 * n);
    for (int &x : v) cin >> x;
    ranges::sort(v);
    vector<int> r(2 * n + 1);
    int s = 0;
    for (int i = 0; v.size() >= n; i += 2) {
        s += (r[i] = v.back()), v.pop_back();
    }
    for (int i = 1; v.size(); i += 2) s -= (r[i] = v.back()), v.pop_back();
    r[2 * n - 1] = s;
    for (int x : r) cout << x << " ";
    cout << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
