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
    int mn = *ranges::min_element(a);
    int mx = *ranges::max_element(a);
    int k = mx - mn + 1;
    auto sorted = a;
    ranges::sort(sorted);
    for (auto [x, y] : views::zip(a, sorted)) {
        if (x != y) { // x cannot be stuck
            k = min(k, max(mx - x, x - mn));
        }
    }
    cout << array{k, (int)-1}[k == mx - mn + 1] << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
