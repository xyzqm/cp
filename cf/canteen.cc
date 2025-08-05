// https://codeforces.com/contest/2089/problem/B2
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void ac() {
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    for (int &x : a) cin >> x;
    for (int &x : b) cin >> x;
    vector<int> nx(n);
    iota(nx.begin(), nx.end(), 0);
    auto cmp = [&](int x, int y) {
        if (int a = nx[x] - x, b = nx[y] - y; a != b) return a < b;
        return x < y;
    };
    set<int, decltype(cmp)> s(cmp);
    for (int i = 0; i < n; i++) s.insert(i);
    set<int> bi;
    for (int i = 0; i < 2 * n; i++) bi.insert(i);
    int sm = accumulate(a.begin(), a.end(), 0LL), lst = -1;
    while (sm > k) {
        assert(s.size() && bi.size());
        auto nh = s.extract(s.begin());
        int i = nh.value();
        if (*bi.lower_bound(i) != nx[i]) {
            assert(*bi.lower_bound(i) > nx[i]);
            nx[i] = *bi.lower_bound(i);
            s.insert(std::move(nh));
            continue;
        }
        assert(nx[i] - i >= lst);
        lst = nx[i] - i;
        int v = min(a[i], b[nx[i] % n]);
        a[i] -= v, b[nx[i] % n] -= v, sm -= v;
        if (!b[nx[i] % n]) {
            bi.erase(nx[i] % n);
            bi.erase(nx[i] % n + n);
        }
        if (a[i]) {
            nx[i] = *bi.lower_bound(i);
            s.insert(std::move(nh));
        }
        else s.erase(i);
    }
    cout << lst + 1 << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
