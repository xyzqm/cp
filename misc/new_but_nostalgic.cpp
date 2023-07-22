#include <iostream>
#include <array>
#include <vector>
#include <string>
using namespace std;
vector<array<int, 26>> trie;
vector<int> cnt, deg;
int n, k, cur;
string ans;
void add(string s) {
    int v = 0;
    for (char c : s) {
        int i = c - 'a';
        if (!trie[v][i]) {
            ++deg[v];
            trie[v][i] = trie.size();
            trie.emplace_back();
            cnt.push_back(0);
            deg.push_back(0);
        }
        v = trie[v][i];
    }
    ++cnt[v];
}
bool dfs(int x = 0, char c = 0) {
    cur += cnt[x] + deg[x] - (c > 0);
    if (cur >= k) {
        if (c) ans.push_back(c);
        return true;
    }
    for (int i = 0; i < 26; i++) {
        if (trie[x][i] && dfs(trie[x][i], 'a' + i)) {
            if (c) ans.push_back(c);
            return true;
        }
    }
    return false;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        trie.assign(1, array<int, 26>());
        cnt.assign(1, 0);
        deg.assign(1, 0);
        ans.clear();
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            add(s);
        }
        cur = 0;
        dfs();
        reverse(ans.begin(), ans.end());
        cout << (ans.size() ? ans : "EMPTY") << endl;
    }
}