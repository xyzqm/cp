#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int inf = 1e15;
using dp = array<array<int, 3>, 3>;
dp id = {{
    {0, -inf, -inf},
    {-inf, -inf, -inf},
    {-inf, -inf, -inf}
}};

void smax(int &a, const int b) { a = max(a, b); }

vector<array<int, 2>> vals;
dp combine(dp a, dp b, int m, int D) { // D = maximum allowed gap
    dp res = id;
    for (auto &w : {0, 1, 2}) for (auto &z : {0, 1, 2}) {
        smax(res[w][z], a[w][0] + b[0][z]);
        for (auto &x : {1, 2}) for (auto &y : {1, 2}) {
            if (m - x < 0 || m + y - 1 >= vals.size()) continue;
            if (vals[m + y - 1][0] - vals[m - x][0] <= D) {
                smax(res[w][z], a[w][x] + b[y][z]);
            }
        }
    }
    return res;
}

int n;
vector<dp> sgt;
void upd(int i, int D, dp val, int p = 1, int l = 0, int r = n / 2) {
    if (r - l == 1) sgt[p] = val;
    else {
        int m = (l + r) >> 1;
        if (i < m) upd(i, D, val, p << 1, l, m);
        else upd(i, D, val, p << 1 | 1, m, r);
        sgt[p] = combine(sgt[p << 1], sgt[p << 1 | 1], m << 1, D);
    }
}

vector<int> calculate_costs(
    vector<int32_t> W, vector<int32_t> A,
    vector<int32_t> B, vector<int32_t> E
) {
    n = W.size();
    int tot = 0;
    for (int i = 0; i < n; i++) {
        tot += A[i];
        vals.push_back({W[i], A[i] - B[i]});
    }
    if (vals.size() % 2) {
        ++n;
        vals.push_back({inf, 0});
    }
    ranges::sort(vals);
    // so we can pair W that is <= E[j] apart, want to maximize sum taken
    vector<array<int, 2>> evts;
    for (int i = 1; i < n; i++) {
        evts.push_back({vals[i][0] - vals[i - 1][0], i >> 1});
        if (i > 1) evts.push_back({vals[i][0] - vals[i - 2][0], i >> 1});
    }
    ranges::sort(evts);

    map<int, int> res;
    sgt.assign(2 * n, id);
    auto sync = [&](int node, int gap) {
        auto [lw, lv] = vals[node << 1];
        auto [rw, rv] = vals[node << 1 | 1];
        dp cur = id;
        if (rw - lw <= gap) cur[0][0] = lv + rv;
        cur[1][1] = lv + rv;
        cur[1][0] = lv, cur[0][1] = rv;
        cur[2][0] = rv, cur[0][2] = lv;
        upd(node, gap, cur);
    };
    for (int i = 0; i < n / 2; i++) sync(i, 0);
    res[0] = sgt[1][0][0];
    for (auto &[gap, node] : evts) {
        sync(node, gap);
        res[gap] = sgt[1][0][0];
    }

    vector<int> qs;
    for (int D : E) {
        auto it = res.upper_bound(D);
        qs.push_back(tot - prev(it)->second);
    }
    return qs;
}
