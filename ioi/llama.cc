#include <bits/stdc++.h>
using namespace std;

#define sz(X) (int)X.size()

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
    for (int k = 0; k + 1 < K; k++) for (int i = 0; i < sz(H); i++) {
        st[k + 1].push_back(max(st[k][i], st[k][min(sz(H) - 1, i + (1 << k))]));
    }
    // find max dist + bottleneck for each val
    vector<pair<int, int>> hs;
    vector<int> low(sz(H));
    ft.resize(sz(H));
    for (int i = 0; i < sz(H); i++) hs.push_back({H[i], i});
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

    vector<int> l(sz(H)), r(sz(H)); // the best you can get from col i is (l[i], r[i]) in row ft[i]
    for (int i = 0; i < sz(H); i++) ev_ft[ft[i]].push_back(i), ev_low[low[i]].push_back(i);
    set<int> s;
    for (int i = -1; i <= sz(H); i++) s.insert(i); // store all blocked indices
    for (auto it = hs.begin(); auto &[k, v] : ev_ft) {
        for (; it != hs.end() && it->first < k; it++) s.erase(it->second);
        for (int x : v) {
            assert(k == -1 || k > H[x]);
            l[x] = *prev(s.upper_bound(x)), r[x] = *s.upper_bound(x);
        }
    }

    s = {-1, sz(H)}; // now store available indices
    for (auto it = hs.begin(); auto &[k, v] : ev_low) {
        for (; it != hs.end() && it->first < k; it++) s.insert(it->second);
        for (int x : v) {
            int a = *s.upper_bound(l[x]), b = *prev(s.lower_bound(r[x]));
            nx[x][0] = {ft[a] < ft[b] ? a : b, a, b};
            if (nx[x][0][1] >= r[x]) nx[x][0] = {x, x, x};
            int y = nx[x][0][0];
            assert(ft[y] >= ft[x]);
            assert(l[y] <= l[x] && r[x] <= r[y]);
        }
    }

    for (int k = 0; k + 1 < K; k++) for (int i = 0; i < sz(H); i++) if (ft[i] >= 0) {
        auto [a, b, c] = nx[i][k];
        auto [d, e, f] = nx[a][k];
        nx[i][k + 1] = {d, max(b, e), min(c, f)};
        assert(ft[d] >= ft[i]);
    }
}

int t = 0;
bool can_reach(int L, int R, int S, int D) {
    if (S > D) swap(S, D);
    int mx = query(S, D + 1);
    for (int k = K; k --> 0; ) if (ft[nx[S][k][0]] <= mx) {
        if (nx[S][k][2] < L) return false;
        S = nx[S][k][0];
    }
    if (ft[S] <= mx && (S == nx[S][0][0] || nx[S][0][2] < L)) return false;

    for (int k = K; k --> 0; ) if (ft[nx[D][k][0]] <= mx) {
        if (nx[D][k][1] > R) return false;
        D = nx[D][k][0];
    }
    if (ft[D] <= mx && (D == nx[D][0][0] || nx[D][0][1] > R)) return false;
    return true;
}

#ifndef ONLINE_JUDGE
int main() {
    int n, m; cin >> n >> m;
    vector<int> T(n), H(m);
    for (int &x : T) cin >> x;
    for (int &x : H) cin >> x;
    initialize(T, H);
    int q; cin >> q;
    while (q--) {
        int l, r, s, d; cin >> l >> r >> s >> d;
        cout << can_reach(l, r, s, d) << endl;
    }
}
#endif
