#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, k;
        long long x;
        cin >> n >> k >> x;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        long long maxWin = n - k + 1;
        if (x > maxWin) {
            cout << 0 << "\n";
            continue;
        }

        vector<long long> cnt(k + 1, 0);
        for (int v : a) cnt[v]++;

        // k = 1
        if (k == 1) {
            if (x != n) {
                cout << 0 << "\n";
            } else {
                for (int i = 0; i < n; i++) cout << a[i] << (i + 1 == n ? '\n' : ' ');
            }
            continue;
        }

        // k = 2
        if (k == 2) {
            long long c2 = cnt[2], c1 = cnt[1];
            vector<int> ans;
            ans.reserve(n);

            if (c2 == x) {
                // all 2s must be in positions 2..n, so position 1 must be 1
                if (c1 == 0) { cout << 0 << "\n"; continue; }
                ans.push_back(1);
                cnt[1]--;
                ans.insert(ans.end(), (int)cnt[2], 2);
                ans.insert(ans.end(), (int)cnt[1], 1);
            } else if (c2 == x + 1) {
                // hide one 2 at position 1
                if (c2 == 0) { cout << 0 << "\n"; continue; }
                ans.push_back(2);
                cnt[2]--;
                ans.insert(ans.end(), (int)cnt[2], 2);
                ans.insert(ans.end(), (int)cnt[1], 1);
            } else {
                cout << 0 << "\n";
                continue;
            }

            if ((int)ans.size() != n) { cout << 0 << "\n"; continue; }
            for (int i = 0; i < n; i++) cout << ans[i] << (i + 1 == n ? '\n' : ' ');
            continue;
        }

        // k >= 3
        vector<int> ans;
        ans.reserve(n);

        auto fail = [&]() {
            cout << 0 << "\n";
        };

        // Build prefix:
        if (x > 0) {
            if (cnt[k] < x) { fail(); continue; }
            cnt[k] -= x; // reserve x copies of k for the "good" ends

            // Build ramp r[1..k-1] with r[i] >= i, using largest available values to preserve small breakers.
            int cur = k;
            vector<int> ramp(k, 0); // 1..k-1 used
            for (int i = k - 1; i >= 1; i--) {
                while (cur > 0 && cnt[cur] == 0) cur--;
                if (cur < i) { fail(); goto next_case; }
                ramp[i] = cur;
                cnt[cur]--;
            }

            for (int i = 1; i <= k - 1; i++) ans.push_back(ramp[i]);
            for (long long i = 0; i < x; i++) ans.push_back(k);
        } else {
            // x == 0: just put a safe prefix of length k-1 using largest values (stashes many k's early)
            int cur = k;
            for (int i = 0; i < k - 1; i++) {
                while (cur > 0 && cnt[cur] == 0) cur--;
                if (cur == 0) { fail(); goto next_case; }
                ans.push_back(cur);
                cnt[cur]--;
            }
        }

        // Now neutralize remaining k's using breaker blocks.
        {
            long long remK = cnt[k];

            long long capSum = 0;
            for (int v = 1; v <= k - 2; v++) {
                capSum += cnt[v] * (long long)(k - v - 1);
            }
            if (remK > capSum) { fail(); goto next_case; }

            vector<pair<int,int>> blocks;
            blocks.reserve((int)min<long long>(remK, n));

            for (int v = 1; v <= k - 2 && remK > 0; v++) {
                int cap = k - v - 1;
                while (cnt[v] > 0 && remK > 0) {
                    int take = (int)min<long long>(remK, cap);
                    blocks.push_back({v, take});
                    cnt[v]--;      // consume this breaker
                    remK -= take;  // consume that many k's
                }
            }
            if (remK != 0) { fail(); goto next_case; }

            cnt[k] = 0; // all remaining k's will be output inside blocks

            // Output all leftover non-k values first (any order is fine)
            for (int v = 1; v <= k - 1; v++) {
                while (cnt[v] > 0) {
                    ans.push_back(v);
                    cnt[v]--;
                }
            }

            // Then output breaker blocks: v followed by 'take' k's (adjacent!)
            for (auto [v, take] : blocks) {
                ans.push_back(v);
                for (int i = 0; i < take; i++) ans.push_back(k);
            }
        }

        if ((int)ans.size() != n) { fail(); goto next_case; }

        for (int i = 0; i < n; i++) cout << ans[i] << (i + 1 == n ? '\n' : ' ');

    next_case:
        continue;
    }

    return 0;
}
