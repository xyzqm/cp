#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

struct bit : vector<int> {
    bit(int n) : vector(n + 1, 0) {}
    void upd(int i, int x) {
        for (++i; i < size(); i += i & -i) at(i) = at(i) + 1;
    }
    int query(int r) {
        int res = 0;
        for (; r; r -= r & -r) res = res + at(r);
        return res;
    }
};

void ac() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    vector<int> b = a;
    sort(b.begin(), b.end());
    map<int, int> compr;
    for (int x : b) if (!compr.count(x)) {
        compr[x] = compr.size();
    }
    for (int &x : a) x = compr[x];
    DBG(compr);
    vector<int> cost(n, n + 1); // min cost for each value
    bit pref(n + 1);
    for (int i = 0; i < n; i++) {
        cost[i] = min(cost[i], pref.query(a[i]));
        pref.upd(a[i], 1);
    }
    bit suf(n + 1);
    for (int i = n; i --> 0; ) {
        cost[i] = min(cost[i], suf.query(a[i]));
        suf.upd(a[i], 1);
    }
    DBG(cost);
    cout << accumulate(cost.begin(), cost.end(), 0LL) << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
