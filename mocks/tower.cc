#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

bool mn = true; // whether we want to minimize or maximize
int d;

struct itv {
    int l, r, val, split;
    int get(int v) {
        assert(l <= v && v < r);
        if (mn) return val;
        else return val + (v - l) / d + ((v % d) >= split);
    }
};

bool operator<(itv a, itv b) {
    return make_pair(a.l, a.r) < make_pair(b.l, b.r);
}

const int inf = 1e13;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    int a, b; cin >> d >> a >> b;
    mn = d * a <= b;
    set<itv> itvs;
    auto process = [&](int l, int r) { // add a new safe interval

    };
    int cur = 0;
    while (n--) {

    }
}
