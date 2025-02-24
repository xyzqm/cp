#include <bits/stdc++.h>
#define int int64_t
#define all(v) v.begin(), v.end()
using namespace std;

const int K = 26;
// pos[i] stores all indices of the ith letter
vector<int> pos[K];
// cnt[i] stores the # of occurences of the ith letter
int cnt[K];

void ac() {
    string s; cin >> s;
    for (int i = 0; i < K; i++) pos[i].clear(), cnt[i] = 0;
    for (int i = 0; i < s.size(); i++) {
        pos[s[i] - 'a'].push_back(i);
        ++cnt[s[i] - 'a'];
    }
    int q; cin >> q;
    while (q--) {
        string t; cin >> t;
        if (t == "?") {
            for (int i = 0; i < K; i++) {
                for (int j : pos[i]) s[j] = 'a' + i;
            }
            cout << s << endl;
            continue;
        }
        vector<int> v;
        for (char c : t) {
            copy(all(pos[c - 'a']), back_inserter(v));
            pos[c - 'a'].clear();
            inplace_merge(v.begin(), v.end() - cnt[c - 'a'], v.end());
        }
        auto it = v.begin();
        for (char c : t) {
            copy(it, it + cnt[c - 'a'], back_inserter(pos[c - 'a']));
            it += cnt[c - 'a'];
        }
    }
}

int32_t main() {
    int t; cin >> t;
    while (t--) ac();
}

