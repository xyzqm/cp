#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

void ac() {
    int n; cin >> n;
    string s; cin >> s;
    int n_1 = ranges::count_if(s, [](char c) { return c == '1'; });
    cout << count_if(s.end() - n_1, s.end(), [](char c) { return c == '0'; }) << endl;

}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
