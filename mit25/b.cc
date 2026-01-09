#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n; cin >> n;
    vector<array<int, 2>> coords(n);
    for (auto &[x, y] : coords) cin >> x >> y;
    sort(coords.begin(), coords.end());
    auto search = [&](int k) {
        auto l = coords.begin(), r = coords.begin();
        int mx = 0;
        while (r != coords.end()) {
            while ((*r)[0] > (*l)[0] + k) mx = max(mx, (*(l++))[1]);
            if (mx > (*r)[1] + k) return false;
            ++r;
        }
        return true;
    };
    int k = 1e10;
    for (int dif = k; dif > 0; dif /= 2) {
        while (k - dif >= 0 && search(k - dif)) k -= dif;
    }
    cout << k << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
