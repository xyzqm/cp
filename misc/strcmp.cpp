#include <iostream>
#include <vector>
#include <array>
#include <string>
using namespace std;
using ll = long long;
vector<vector<pair<char, int>>> trie;
vector<ll> c1, c2;
ll ans = 0;
// add null character to end of string?
void add(string s) {
    int v = 0;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        ans += (2 * i + 1) * (c1[v] - c2[v]);
        int nxt = -1;
        // cout << c1[v] << " " << c2[v] << " ";
        for (auto p : trie[v]) if (p.first == c) {
            ans -= (2 * i + 1) * c1[p.second];
            nxt = p.second;
            break;
        }
        // cout << endl;
        ++c1[v];
        if (nxt < 0) {
            trie[v].push_back({c, nxt = trie.size()});
            trie.emplace_back();
            c1.push_back(0);
            c2.push_back(0);
        }
        v = nxt;
    }
    ans += 2 * s.length() * c2[v];
    ++c1[v];
    ++c2[v];
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, c = 0;
    while (cin >> n) {
        if (n == 0) break;
        trie.assign(1, vector<pair<char, int>>());
        c1.assign(1, 0);
        c2.assign(1, 0);
        ans = 0;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            s.push_back(0);
            add(s);
        }
        cout << "Case " << ++c << ": " << ans << endl;
    }
}