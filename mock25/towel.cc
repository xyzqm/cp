#include <bits/stdc++.h>
using namespace std;

const int K = 21;

int a[2 * K];

int main() {
    set<int> l{0}, r{0};
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) {
        set<int> &s = (i < K ? l : r);
        vector<int> v;
        if (s.count(a[i])) {
            cout << a[i] << endl;
            exit(0);
        }
        for (int x : s) v.push_back(x + a[i]);
        for (int x : v) s.insert(x);
    }
    for (int s : l) if (r.count(s)) {
        cout << s << endl;
        break;
    }
    assert(false);
}
