#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int ac() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    int cur = -1;
    for (int x : a) {
        if (x == 0) return 0;
        else if (x > 0) {
            if (cur > 0 && x != cur) return 0;
            else cur = x;
        }
    }
    return 1;
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << array{"NO", "YES"}[ac()] << endl;
}
