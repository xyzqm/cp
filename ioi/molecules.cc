#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

std::vector<int> find_subset(int l, int u, vector<int> w) {
    #define int int64_t
    int n = w.size();
    vector<array<int, 2>> vals;
    for (int i = 0; int v : w) { vals.push_back({v, i++}); };
    ranges::sort(vals);
    for (int i = 0, mn = 0, mx = 0; i < n; i++) {
        mn += vals[i][0], mx += vals[n - i - 1][0];
        if (mn <= u && mx >= l) { // viable solution exists!
            int sm = 0;
            deque<signed> dq;
            auto push = [&](int i) { dq.push_back(vals[i][1]), sm += vals[i][0]; };
            auto pop = [&]() { sm -= w[dq.front()], dq.pop_front(); };
            for (int j = 0; j <= i; j++) push(j);
            for (int j = i + 1; j < n; j++) {
                if (sm >= l) break;
                else pop(), push(j);
            }
            return ranges::to<vector>(dq);
        }
    }
    return {};
}

#ifndef ONLINE_JUDGE
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    auto v = find_subset(15, 17, {6, 8, 8, 7});
    DBG(v);
    auto v2 = find_subset(10, 20, {15, 17, 16, 18});
    DBG(v2);
}
#endif
