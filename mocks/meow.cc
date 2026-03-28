#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n, m, k; cin >> n >> m >> k;
    vector<queue<int>> pos(k + 1);
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        pos[a[i]].push(i);
    }
    vector<deque<int>> stacks(n + 1);
    vector<int> loc(k + 1);
    int cur = 0;
    auto is_top = [&](int v) {
        int stk = loc[v];
        return stacks[stk].size() == 1 || stacks[stk][1] == v;
    };
    auto bot_first = [&](deque<int> &stk, int t) {
        for (int &v : stk) while (pos[v].front() <= t) pos[v].pop();
        return pos[stk[0]].front() < pos[stk[1]].front();
    };
    for (int t = -1; int x : a) {
        t++;
        int empty = 0;
        for (int i = 1; i <= n; i++) if (!stacks[i].size()) empty = i;
        if (loc[x]) {
            if (is_top(x)) {
                cout << "1 " << loc[x] << "\n";
                stacks[loc[x]].pop_back();
            }
            else {
                assert(empty);
                cout << "1 " << empty << "\n";
                cout << "2 " << loc[x] << " " << empty << "\n";
                stacks[loc[x]].pop_front();
            }
            loc[x] = 0;
        }
        else {
            int nx_bot = 0;
            for (int i = 1; i <= n; i++) {
                if (stacks[i].size() < 2) {
                    loc[x] = i;
                    stacks[i].push_back(x);
                    goto placed;
                }
                else if (bot_first(stacks[i], t)) nx_bot = i;
            }
        }
        placed:
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
