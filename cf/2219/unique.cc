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
    vector<int> cur;
    auto contains3 = [&](int suf) {
        vector<int> q = cur;
        for (int i = suf; i <= 2 * n + 1; i++) q.push_back(i);
        cout << "? " << q.size() << " ";
        for (int x : q) cout << x << " ";
        cout << endl;
        int v; cin >> v;
        return (v & 1) != (q.size() & 1);
    };
    while (cur.size() < 3) {
        int pos = cur.size() ? cur.back() + 1 : 1;
        for (int dif = 1 << 10; dif > 0; dif /= 2) {
            if (contains3(pos + dif)) pos += dif;
        }
        cur.push_back(pos);
    }
    assert(cur.size() == 3);
    cout << "! ";
    for (int x : cur) cout << x << " ";
    cout << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
