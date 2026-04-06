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
    vector<int> res(n);
    for (int i = 0, cur = (n + 1) / 2; i < n; i += 2) res[i] = cur--;
    for (int i = 1, cur = (n + 1) / 2 + 1; i < n; i += 2) res[i] = cur++;
    for (int x : res) cout << x << " ";
    cout << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
