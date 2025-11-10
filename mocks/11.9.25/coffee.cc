#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t; cin >> n >> t;
    vector<int> reach(n);
    reach[0] = 1;
    for (int i = 1; t; i = i * 2 % n, t >>= 1) if (t & 1) {
        vector<int> nx(n);
        for (int j = 0; j < n; j++) if (reach[j]) {
            nx[(j + i) % n] ^= 1;
            nx[(j + n - i) % n] ^= 1;
        }
        reach.swap(nx);
    }
    string s; cin >> s;
    for (int i = 0; i < n; i++) {
        int v = 0;
        for (int j = 0; j < n; j++) if (reach[j]) {
            int nx = (i + j) % n;
            if (s[nx] == '1') v ^= 1;
        }
        cout << v;
    }
    cout << endl;
}
