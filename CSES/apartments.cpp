#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for (int& x : a) cin >> x;
    for (int& x : b) cin >> x;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int ans = 0;
    int ai = 0, bi = 0;
    while (ai < a.size() && bi < b.size()) {
        if (abs(a[ai] - b[bi]) <= k) {
            ans++;
            ai++;
            bi++;
        } else if (a[ai] < b[bi]) ai++;
        else bi++;
    }
    cout << ans << endl;
}