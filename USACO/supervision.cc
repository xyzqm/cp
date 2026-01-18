#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int M = 1e9 + 7;

const int I2 = (M + 1) / 2;

void mul(int &a, int b) { a = a * b % M; }
void ad(int &a, int b) { a = (a + b) % M; }
void sb(int &a, int b) {a = (a - b + M) % M; }

/*
Solution sketch:
Let dp[i] be the number of valid configurations in which
a subset of the coaches [0, i) are selected, including coach i - 1.

For an n^2 transition, transition
dp[i] <- dp[lst] * 2^(new cows introduced)

To optimize to O(n), observe that all overlapping choices
of lst will double in contribution whenever a new camper
is encountered, until they stop overlapping. Therefore,
we can easily update from i to i + 1.
*/

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, d; cin >> n >> d;
    vector<array<int, 2>> cows(n);
    for (auto &[p, t] : cows) cin >> p >> t;
    int ans = 0;
    // contribution of prev dp values
    int overlap = 0, outside = 1;
    // number of subsets of campers within our current interval
    int s_in = 1;
    using it_t = decltype(cows)::iterator;
    queue<pair<int, it_t>> q; // current overlapping intervals
     // rr is the first val that is > d away from cur
    it_t rr = cows.begin();
    for (auto &[p, t] : cows) {
        while (q.size()) {
            auto [val, it] = q.front();
            if (it != cows.end() && (*it)[0] == p) {
                sb(overlap, val * s_in % M);
                ad(outside, val);
                q.pop();
            }
            else break;
        }
        while (rr != cows.end() && (*rr)[0] <= p + d) {
            if ((*rr)[1] == 0) {
                mul(s_in, 2);
                mul(overlap, 2);
            }
            rr++;
        }
        if (t == 1) {
            int dp = (outside * s_in % M) + overlap;
            ad(ans, dp %= M);
            q.push({dp, rr});
            ad(overlap, dp);
        }
        if (t == 0) mul(s_in, I2);
    }
    cout << ans << endl;
}
