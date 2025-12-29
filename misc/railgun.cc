// https://qoj.ac/problem/6420
#include <bits/stdc++.h>
using namespace std;

#define int int64_t

// sliding window minimum
struct slide : deque<array<int, 2>> { // store [index, max]
    int idx = 0, l_idx = 0;
    void push(int v) {
        while (size() && v < back()[1]) pop_back();
        push_back({idx++, v});
    }
    void pop() {
        if (size() && l_idx++ == front()[0]) pop_front();
    }
    int min() {
        return size() ? at(0)[1] : 1e12;
    }
};

struct itv {
    int mn = 0, mx = 0;
    void operator+=(int x) {
        mn = min(mn, x);
        mx = max(mx, x);
    }
};

itv operator+(itv a, int x) { return a += x, a; }

void ac() {
    int n; cin >> n;
    vector<array<int, 2>> pts(n);
    for (auto &[x, y]: pts) cin >> x >> y;
    pts.push_back(array<int, 2>{0, 0});
    ranges::sort(pts);
    int ans = 1e12;
    auto flip = [&]() { for (auto &[x, y] : pts) y = -y; };

    auto nut = [&](function<int(itv)> L, function<int(itv)> R, function<bool(itv, itv)> pref, function<bool(itv, itv)> suf) {
        slide s; // slide contains [it_a, it_b)
        itv rr = {0, 0};
        deque<itv> ls(1, {0, 0});

        auto it_a = pts.begin(), it_b = pts.begin();
        auto it_r = pts.rbegin();

        for( ; it_r != pts.rend() && (*it_r)[0] >= 0; it_r++) {
            while (it_b != pts.end() && (*it_b)[0] <= 0) {
                auto [_, y_l] = *it_b;
                if (pref(ls.back(), rr)) { // extend prefix
                    s.push(-2 * (*it_b)[0] + L(ls.back()));
                    ls.push_back(ls.back() + y_l);
                    it_b++;
                }
                else break;
            }
            while (it_a < it_b && !suf(ls.front(), rr)) { // delete invalid suffix
                ls.pop_front();
                s.pop();
                it_a++;
            }
            ans = min(ans, (*it_r)[0] + R(rr) + s.min());
            rr += (*it_r)[1];
        }
    };

    auto win = [&]() {
        // left within right
        nut(
            [](itv _) { return 0; },
            [](itv iv) { return 2 * iv.mx - iv.mn; },
            [](itv a, itv b) { return a.mx <= b.mx && a.mn >= b.mn; },
            [](itv a, itv b) { return true; }
        );

        // right within left
        nut(
            [](itv iv) { return 2 * iv.mx - iv.mn; },
            [](itv _) { return 0; },
            [](itv a, itv b) { return true; },
            [](itv b, itv a) { return a.mx <= b.mx && a.mn >= b.mn; }
        );

        // left above right
        nut(
            [](itv ll) { return 2 * ll.mx; },
            [](itv rr) { return -rr.mn; },
            [](itv l, itv r) { return l.mn >= r.mn; },
            [](itv l, itv r) { return l.mx >= r.mx; }
        );

        // left below right
        nut(
            [](itv ll) { return -ll.mn; },
            [](itv rr) { return 2 * rr.mx; },
            [](itv l, itv r) { return l.mx <= r.mx; },
            [](itv l, itv r) { return l.mn <= r.mn; }
        );
    };

    win(); flip(); win();
    for (auto &[x, y] : pts) x = -x;
    ranges::reverse(pts);
    win(); flip(); win();
    cout << ans << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
