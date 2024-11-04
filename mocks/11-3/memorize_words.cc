#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5;

vector<array<int, 26>> trie(1);
vector<int> cnt(1);
string a[N];

void insert(string s) {
    reverse(s.begin(), s.end());
    int x = 0;
    for (char c : s) {
        if (!trie[x][c - 'a']) {
            trie[x][c - 'a'] = trie.size();
            trie.push_back({});
            cnt.push_back(0);
        }
        x = trie[x][c - 'a'];
    }
    ++cnt[x];
}

struct T { ll sz, cost;
    bool operator<(const T& o) const { return sz < o.sz; }
};
vector<T> dp(int x) {
    vector<T> v;
    for (int y : trie[x]) if (y) {
        vector<T> z = dp(y);
        if (v.size() < z.size()) v.swap(z);
        for (T t : z) v.push_back(t);
    }
    if (x && !cnt[x]) return v;
    ll r = 1, c = 0;
    sort(v.begin(), v.end());
    for (auto [sz, cost] : v) {
        r += c + cost, c += sz;
    }
    return {{c + 1, r}};
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) insert(a[i]);
    cout << dp(0)[0].cost - 1 << endl;
}
