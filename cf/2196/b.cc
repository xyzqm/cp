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
    vector<int> a(n);
    for (int &x : a) cin >> x;
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int v = 1; v <= min(n / a[i], a[i]); v++) {
            int prod = a[i] * v;
            if (prod <= i && a[i - prod] == v) ++res;
            if (i + prod < n && a[i + prod] == v) res += v < a[i];
        }
    }
    cout << res << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
