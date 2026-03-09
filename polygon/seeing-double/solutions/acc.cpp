#include <bits/stdc++.h>
using namespace std;

#define int int64_t

struct bit : vector<int> {
    bit(int n) : vector(n + 1, 0) {}
    void upd(int i, int x) {
        for (++i; i < size(); i += i & -i) at(i) = at(i) + 1;
    }
    int query(int r) {
        int res = 0;
        for (; r; r -= r & -r) res = res + at(r);
        return res;
    }
};

int ac() {
    string s; cin >> s;
    vector<int> frq(26);
    for (char c : s) ++frq[c - 'a'];
    for (int &x : frq) {
        assert(!(x % 2));
        x >>= 1;
    }
    vector<int> mp(s.size());
    vector<queue<int>> pos(26);
    int half = s.size() / 2, fst = 0;
    for (int i = 0; i < s.size(); i++) {
        if (pos[s[i] - 'a'].size() == frq[s[i] - 'a']) {
            mp[i] = pos[s[i] - 'a'].front() + half;
            pos[s[i] - 'a'].pop();
        }
        else mp[i] = fst++;
        pos[s[i] - 'a'].push(mp[i]);
    }
    bit fen(s.size());
    int inv = 0;
    for (int x : mp) {
        inv += fen.query(s.size() - 1 - x);
        fen.upd(s.size() - 1 - x, 1);
    }
    return inv;
}

int32_t main() {
    int t; cin >> t;
    while (t--) cout << ac() << "\n";
}
