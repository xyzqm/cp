#include <bits/stdc++.h>
using namespace std;

int query(string str);

// using characters in range [l, r)
string sub(int n, char l, char r) {
    if (r - l == 1) return string(query(string(n, l)), l);
    else {
        char m = (l + r) >> 1;
        string L = sub(n, l, m), R = sub(n, m, r);
        int lt = 0, rt = 0;
        while (lt < L.size() && rt < R.size()) {
            L.insert(L.begin() + lt, R[rt]);
            if (query(L) == L.size()) rt++;
            else L.erase(L.begin() + lt);
            lt++;
        }
        while (rt < R.size()) L += R[rt++];
        return L;
    }
};

string guess(int n, int s) {
    return sub(n, 'a', 'a' + s);
}
