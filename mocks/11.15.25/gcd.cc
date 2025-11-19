#include <bits/stdc++.h>
using namespace std;

const int A = 200001;

// monotonic set
struct mono : set<array<int, 2>> {
    void insert(array<int, 2> v) {
        auto it = lower_bound(v);
        if (it != end() && it->at(1) >= v[1]) return;
        while ((it = lower_bound(v)) != begin()) {
            it = prev(it);
            if (it->at(1) < v[1]) erase(it);
            else break;
        }
        set::insert(v);
    }
    int query(int l) {
        return lower_bound({l, 0})->at(1);
    }
};

vector<int> f[A];

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int i = A; i --> 1; ) for (int j = i; j < A; j += i) f[j].push_back(i);

    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    int q; cin >> q;
    vector<vector<array<int, 2>>> qs(n);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        qs[--r].push_back({--l, i});
    }
    vector<int> lst(A, -1), res(q);
    mono opts;
    opts.insert({n, 0});
    for (int i = 0; i < n; i++) {
        for (int j : f[a[i]]) {
            if (lst[j] >= 0) opts.insert({lst[j], j});
            lst[j] = i;
        }
        for (auto [l, j] : qs[i]) res[j] = opts.query(l);
    }
    for (int x : res) cout << x << "\n";
}
