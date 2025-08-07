#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void ac() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m), lis(n);
    for (int &x : a) cin >> x;
    for (int &x : b) cin >> x;
    set<array<int, 2>> s = {{0, 0}};
    for (int i = 0; i < n; i++) {
        auto it = s.lower_bound({a[i], 0});
        auto p = array{a[i], prev(it)->at(1) + 1};
        lis[i] = p[1];
        while ((it = s.lower_bound(p)) != s.end()) {
            if (it->at(1) >= p[1]) break;
            s.erase(it);
        }
        if (prev(it)->at(1) < p[1]) s.insert(p);
    }
    ranges::sort(b, greater<int>());
    vector<int> c;
    auto it_a = a.begin(), it_b = b.begin();
    int mx = *ranges::max_element(lis);
    while (it_a != a.end() && it_b != b.end()) {
        if (lis[it_a - a.begin()] == mx) {
            while (it_b != b.end() && *it_b >= *it_a) c.push_back(*(it_b++));
        }
        c.push_back(*(it_a++));
    }
    copy(it_a, a.end(), back_inserter(c));
    copy(it_b, b.end(), back_inserter(c));
    for (int x : c) cout << x << " ";
    cout << endl;
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}
