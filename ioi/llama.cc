#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

const int N = 2e5 + 1;
const int K = 20;

array<int, 3> nx[N][K]; // result + min and max indices to jump to segment
vector<int> ft, st[K];

int query(int l, int r) {
    assert(l < r);
    int lg = __lg(r - l);
    return max(st[lg][l], st[lg][r - (1 << lg)]);
}

void initialize(vector<int> T, vector<int> H) {
    // build sparse table
    st[0] = H;
    for (int k = 0; k + 1 < K; k++) for (int i = 0; i < H.size(); i++) {
        st[k + 1].push_back(max(st[k][i], st[k][min((int)H.size() - 1, i + (1 << k))]));
    }
    // find max dist + bottleneck for each val
    vector<pair<int, int>> hs;
    vector<int> low(H.size());
    ft.resize(H.size());
    for (int i = 0; i < H.size(); i++) hs.push_back({H[i], i});
    ranges::sort(hs);
    int mx = -1, mn = 1e9 + 1;
    map<int, vector<int>> ev_ft, ev_low;
    T.push_back(0);
    T.push_back(1e9 + 1); // to ensure all ft and low values are set
    for (auto r_it = hs.rbegin(); int x : T) {
        mn = min(mn, x);
        if (x > mx) {
            for (; r_it != hs.rend() && r_it->first >= mn; ++r_it) { // cut off everything >= bottleneck
                ft[r_it->second] = mx;
                low[r_it->second] = mn;
            }
            mx = x;
        }
    }
    DBG(ft);
    DBG(low);

    vector<int> l(H.size()), r(H.size()); // the best you can get from col i is (l[i], r[i]) in row ft[i]
    for (int i = 0; i < H.size(); i++) ev_ft[ft[i]].push_back(i), ev_low[low[i]].push_back(i);
    set<int> s;
    for (int i = -1; i <= (int)H.size(); i++) s.insert(i); // store all blocked indices
    DBG(s);
    for (auto it = hs.begin(); auto &[k, v] : ev_ft) {
        for (; it != hs.end() && it->first < k; it++) s.erase(it->second);
        for (int x : v) {
            assert(k == -1 || k > H[x]);
            DBG(s);
            DBG(x);
            l[x] = *prev(s.upper_bound(x)), r[x] = *s.upper_bound(x);
        }
    }

    s = {-1, (int)H.size()}; // now store available indices
    for (auto it = hs.begin(); auto &[k, v] : ev_low) {
        for (; it != hs.end() && it->first < k; it++) s.insert(it->second);
        for (int x : v) {
            nx[x][0] = {*s.upper_bound(l[x]), *s.upper_bound(l[x]), *prev(s.lower_bound(r[x]))};
            if (nx[x][0][1] >= r[x]) nx[x][0] = {x, x, x};
            assert(ft[nx[x][0][0]] >= ft[x]);
        }
    }

    for (int k = 0; k + 1 < K; k++) for (int i = 0; i < H.size(); i++) if (ft[i] >= 0) {
        auto [a, b, c] = nx[i][k];
        auto [d, e, f] = nx[a][k];
        nx[i][k + 1] = {d, max(b, e), min(c, f)};
        assert(ft[d] >= ft[i]);
    }
}

bool can_reach(int L, int R, int S, int D) {
    if (S > D) swap(S, D);
    int mx = query(S, D + 1);
    if (min(ft[S], ft[D]) > mx) return true;
    for (int &v : {ref(S), ref(D)}) {
        int t = (v == D);
        for (int k = K; k --> 0; ) if (ft[nx[v][k][0]] <= mx) {
            if (!t && nx[v][k][2] < L || t && nx[v][k][1] > R) return false;
            v = nx[v][k][0];
        }
    }
    if (ft[nx[S][0][0]] <= mx || nx[S][0][2] < L || ft[nx[D][0][0]] <= mx || nx[D][0][1] > R) return false;
    return true;
}

#ifndef ONLINE_JUDGE
int main() {
    // auto v = ranges::to<vector>(views::iota(1, 2e5 + 1));
    // initialize(v, v);
 // for (int i = 0; i < 20000; i++) can_reach(i / 2, i, i / 2, i);
    initialize(
        {8, 6, 10, 4, 4, 4, 12, 6, 8, 14},
        {3, 7, 13, 7, 5, 7, 9, 7, 3, 5, 11, 13, 7, 3}
    );
    DBG(can_reach(2, 10, 3, 8));
    DBG(can_reach(2, 10, 5, 8));
    DBG(can_reach(5, 10, 5, 8));
    // initialize({2, 1, 3}, {0, 1, 2, 0});
    // DBG(can_reach(0, 3, 1, 3));
    // DBG(can_reach(1, 3, 1, 3));
}
#endif
