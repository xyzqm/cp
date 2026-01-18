#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> boxes(m); for (int &x : boxes) cin >> x;
    vector<array<int, 3>> friends(n);
    for (auto &[x, y, z] : friends) {
        cin >> x >> y >> z;
        k -= y;
    }
    multiset<int> difs;
    ranges::sort(boxes);
    ranges::sort(friends);
    auto it = friends.begin();
    int ans = 0;
    for (int &box : boxes) {
        for (; it != friends.end() && (*it)[0] <= box; it++) difs.insert((*it)[2] - (*it)[1]);
        if (difs.size()) difs.erase(--difs.end()), ans++;
    }
    for (; it != friends.end(); it++) difs.insert((*it)[2] - (*it)[1]);
    DBG(difs);
    for (int dif : difs) if (k >= dif) k -= dif, ++ans;
    cout << ans << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
