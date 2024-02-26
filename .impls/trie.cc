#include <vector>
#include <array>
#include <string>
using namespace std;
vector<array<int, 26>> trie;
vector<int> cnt, deg;
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