#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<int> kmp(T s, T p) {
    vector<int> pre(p.size() + 1);
    for (int i = 1; i < p.size(); i++) {
        int j = pre[i];
        while (j && p[j] != p[i]) j = pre[j];
        pre[i + 1] = j + (p[j] == p[i]);
    }
    vector<int> kmp(s.size() + 1);
    for (int i = 0; i < s.size(); i++) {
        int j = kmp[i];
        while (j && p[j] != s[i]) j = pre[j];
        kmp[i + 1] = j + (p[j] == s[i]);
    }
    return kmp;
}

int32_t main() {
    string s, p; cin >> s >> p;
    cout << ranges::count_if(kmp(s, p), [&p](int x) { return x == p.size(); }) << endl;
}
