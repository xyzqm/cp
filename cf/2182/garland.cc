#include <bits/stdc++.h>
using namespace std;

#define int int64_t

/*
Let dp[i][d] be the number of ways to start from node i,
hang the garland in i's subtree, and end at a node of depth d (relative to i).

To transition, we pick all but one child to end at depth < k, and that remaining child
becomes the final depth (which may or may not be < k).

To speed this up, we can merge smaller chains into larger chains for overall O(n).
*/

const int M = 998244353;

int inv(int x) {
    assert(x > 0);
    int r = 1;
    for (int exp = M - 2; exp; exp >>= 1, x = x * x % M) if (exp & 1) r = r * x % M;
    return r;
}

void ad(int &a, const int b) { a = (a + b) % M; }

struct lz : deque<int> {
    int mul = 1, add = 0;

    void mult(int v, int sz) {
        assert(sz <= size());
        v %= M;
        if (!v) {
            assign(sz, 0), mul = 1, add = 0;
        }
        else {
            mul = mul * v % M;
            add = add * v % M;
        }
    }
    void operator+=(int v) { ad(add, v); }
    int operator[](int i) const {
        return i >= 0 && size() ?
            (at(min((int)size() - 1, i)) * mul + add) % M :
            0;
    }
    void swap(lz &o) {
        deque::swap(o);
        ::swap(mul, o.mul);
        ::swap(add, o.add);
    }
    void operator+=(lz &o) {
        assert(size() >= o.size());
        int iv = inv(mul);
        for (int i = 0; i < o.size(); i++) {
            ad(at(i), iv * o[i]);
        }
    }
    void push_front(int x) {
        int iv = inv(mul);
        deque::push_front(iv * (x + M - add) % M);
    }
};

void ac() {
    int n, k; cin >> n >> k;
    vector<int> fa(n + 1), deg(n + 1);
    for (int i = 2; i <= n; i++) cin >> fa[i];
    vector<lz> dp(n + 1);
    for (int i = n; i > 1; i--) {
        dp[i].push_front(!dp[i].size()); // if empty, push 1, else push 0
        if (!deg[fa[i]]) dp[fa[i]].swap(dp[i]);
        else {
            int l_mul = 1, r_mul = deg[fa[i]]; // multiplier when dp[fa[i]] is on the left/right
            if (dp[fa[i]].size() < dp[i].size()) swap(l_mul, r_mul), dp[fa[i]].swap(dp[i]);

            // case 1: fa[i] on the left
            int tmp = dp[i][k - 2];
            dp[i].mult(l_mul * dp[fa[i]][k - 2], dp[i].size());
            // case 2: fa[i] on the right
            dp[fa[i]].mult(r_mul * tmp, dp[i].size());
            // merge two cases
            dp[fa[i]] += dp[i][dp[i].size() - 1];
            dp[i] += M - dp[i][dp[i].size() - 1];
            dp[fa[i]] += dp[i];
        }
        ++deg[fa[i]];
    }
    cout << dp[1][dp[1].size() - 1] << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
