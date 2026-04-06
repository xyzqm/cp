#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n, k, l; cin >> n >> k >> l;
    vector<int> pos(n);
    for (int &x : pos) cin >> x;
    ranges::sort(pos.begin(), pos.end());
    vector<int> difs;
    adjacent_difference(pos.begin(), pos.end(), back_inserter(difs));
    difs.erase(difs.begin());
    ranges::sort(difs, greater());
    difs.push_back(0);
    DBG(difs);
    int ans = 0;
    for (int t = 0, tot = 0; int d : difs) {
        if (k - 1 - t < 0) {
            ans = max(ans, tot / 2);
            break;
        }
        ans = max(ans, max(pos[0], l - pos.back()) + tot + (k - 1 - t++) * (l - (pos.back() - pos[0] - tot)));
        tot += d;
    }
    cout << ans << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
