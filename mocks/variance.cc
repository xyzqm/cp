#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    while (true) {
        bool found = false;
        for (int i = 1; i + 1 < n; i++) {
            if (a[i - 1] + a[i + 1] > 2 * a[i]) {
                a[i] = a[i - 1] + a[i + 1] - a[i];
                found = true;
            }
        }
        if (found) continue;
        else break;
    }
    int sm = accumulate(a.begin(), a.end(), 0LL);
    int var = 0;
    for (int &x : a) {
        var += (n * x - sm) * (n * x - sm);
    }
    assert(var % n == 0);
    DBG(a);
    cout << var / n << "\n";
}
