#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int inf = 1LL << 40;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    for (int &x : a) cin >> x;
    for (int &x : b) cin >> x;
    auto pen = [&](int p) {
        for (int &x : a) x -= p;
        int cnt = 0, tot = 0;
        priority_queue<int, vector<int>, greater<int>> pq_a;
        priority_queue<int> pq_b;
        for (auto [a, b] : views::zip(a, b)) {
            pq_a.push(a);
            if (int v1 = pq_a.top() + b, v2 = b - (pq_b.size() ? pq_b.top() : -inf); min(v1, v2) < 0) {
                tot += min(v1, v2);
                if (v1 < v2) ++cnt, pq_a.pop();
                else pq_b.pop();
                pq_b.push(b);
            }
        }
        for (int &x : a) x += p;
        return array{cnt, tot};
    };
    int p = 0;
    for (int dif = inf; dif > 0; dif /= 2) {
        if (pen(p + dif)[0] <= k) p += dif;
    }
    cout << pen(p)[1] + p * k << endl;
}
