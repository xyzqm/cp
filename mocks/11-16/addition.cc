#include <algorithm>
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 1;
int n, m, k, a, v[N], l[N], r[N];

bool ck(int x) {
    auto cmp1 = [&](int i, int j) { return l[i] > l[j]; };
    auto cmp2 = [&](int i, int j) { return r[i] < r[j]; };
    auto cmp3 = [&](int i, int j) { return r[i] > r[j]; };
    priority_queue<int, vector<int>, decltype(cmp1)> opt(cmp1);
    priority_queue<int, vector<int>, decltype(cmp2)> open(cmp2);
    priority_queue<int, vector<int>, decltype(cmp3)> used(cmp3);
    for (int i = 0; i < m; i++) opt.push(i);
    int t = 0;
    for (int i = 1; i <= n; i++) {
        while (opt.size() && l[opt.top()] == i) {
            open.push(opt.top());
            opt.pop();
        }
        while (v[i] + a * used.size() < x) {
            if (!open.size() || r[open.top()] < i) return false;
            used.push(open.top()), ++t;
            open.pop();
        }
        while (used.size() && r[used.top()] == i) used.pop();
    }
    // cout << opt.size() << " " << open.size() << " " << used.size() << endl;
    // assert(!opt.size() && !open.size() && !used.size());
    return t <= k;
}

void ac() {
    cin >> n >> m >> k >> a;
    for (int i = 1; i <= n; i++) cin >> v[i];
    for (int i = 0; i < m; i++) cin >> l[i] >> r[i];
    int x = 0, r = *max_element(v, v + n + 1) + k * a;
    for (int d = r; d > 0; d >>= 1) {
        while (x + d <= r && ck(x + d)) x += d;
    }
    cout << x << endl;
}

signed main() {
    int t; cin >> t;
    while (t--) ac();
}
