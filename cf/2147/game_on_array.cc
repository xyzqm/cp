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
    map<int, int> frq;
    int tot = 0;
    while (n--) {
        int v; cin >> v;
        tot += v;
        if (v & 1) ++frq[v];
    }
    vector<int> difs;
    for (auto &[_, cnt] : frq) difs.push_back(cnt);
    ranges::sort(difs, greater());
    int alt = 0;
    for (int i = 0; int d : difs) {
        alt += (i++ & 1) ? -d : d;
    }
    DBG(alt);
    cout << (tot - alt) / 2 + alt << " " << (tot - alt) / 2 << "\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
