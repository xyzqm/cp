#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

struct node { int tot, sm, ones; };

int cnt = 0;
int ac() {
    int n, m; cin >> n >> m;
    vector<array<int, 2>> vs(n);
    int ans = 0;
    multiset<array<int, 2>, greater<>> slopes; // {slope, len}
    // vector<array<int, 2>> slps;
    multiset<array<int, 2>, greater<>> front, back;
    int ones = 0, tot_len = 0, val = 0;
    auto add_front = [&](array<int, 2> ln) {
        auto [slp, len] = ln;
        tot_len += len;
        ones += (len == 1);
        val += slp * len / 2;
        front.insert(ln);
    };
    auto rem_front = [&](array<int, 2> ln) {
        auto [slp, len] = ln;
        front.erase(front.find(ln));
        tot_len -= len;
        ones -= (len == 1);
        val -= slp * len / 2;
    };
    multiset<int, greater<int>> free; // ones to use in the back
    auto del = [&](array<int, 2> ln) {
        if (front.find(ln) != front.end()) rem_front(ln);
        else {
            back.erase(back.find(ln));
            if (ln[1] == 1) free.erase(free.find(ln[0]));
        }
    };
    // maintain positive slopes & sufficiently small lengths
    auto upd_mx = [&](int cnt, int need) {
        // int front_len = min(m - 1, m - 3 + ones);
        while (back.size()
            && (*back.begin())[0] > 0
            && tot_len + (*back.begin())[1] <= cnt
        ) {
            auto ln = *back.begin();
            add_front(ln);
            back.erase(back.begin());
            if (ln[1] == 1) free.erase(free.find(ln[0]));
        }
        while (front.size() && (tot_len + max((int)0, need - ones) > cnt || (*front.rbegin())[0] <= 0)) {
            auto lst = *front.rbegin();
            rem_front(lst);
            back.insert(lst);
            if (lst[1] == 1) free.insert(lst[0]);
        }
        // DBG(cnt);
        // DBG(need);
        // assert(tot_len + max((int)0, need - ones) <= cnt);
        assert(cnt < 0 || tot_len <= cnt);
        cnt -= tot_len;
        int res = val;
        for (auto f : free) {
            if (need <= ones || cnt <= 0) break;
            else res += f / 2, need--, cnt--;
        }
        if (need <= ones) ans = max(ans, res);
    };
    // auto upd_mx = [&](int cnt, int need) {
    //     cnt = cnt - tot_len; // how many we have to get from back
    //     need = need - ones; // how many ones we need from the back

    //     ans = max(ans, )
    //     // int cur = 0;
    //     // for (auto &[s, len] : slopes)
    //     // if (cnt - len >= 0)
    //     // if (len == 1 || (cnt >= len + need && s > 0)) {
    //     //     cur += s * len / 2, cnt -= len;
    //     //     need -= (len == 1);
    //     //     if (need <= 0) ans = max(ans, cur);
    //     // }
    // };
    for (auto &[b, a] : vs) {
        cin >> a >> b;
        slopes.insert({2 * (a + b), 1});
        add_front({2 * (a + b), 1});
        // slps.push_back({2 * (a + b), i});
        // slps.push_back({2 * a, i});
    }
    // fix();
    // ranges::sort(slps, greater<>());
    sort(vs.begin(), vs.end(), [&](array<int, 2> a, array<int, 2> b) {
       return array{a[0], a[1]} < array{b[0], b[1]};
    });

    upd_mx(m, 2 - (m == 1));

    for (auto &[b, a]: vs) {
        slopes.erase(slopes.find({2 * (a + b), 1}));
        // DBG(front);
        // DBG(back);
        del({2 * (a + b), 1});
        add_front({a, 2});
        slopes.insert({a, 2});
        // fix();
        DBG(front);
        DBG(back);
        DBG(ones);
        DBG(tot_len);
        // DBG(slopes);
        upd_mx(m - 1, 2);
    }
    upd_mx(m, 0);
    return ans;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int s, t; cin >> s >> t;
    while (t--) cout << ac() << "\n";
}
