#include <bits/stdc++.h>
using namespace std;

const int K = 30;

struct trie : vector<array<int, 2>> {
    trie() : vector(2) {}
    int lz = 0;
    void insert(int x) {
        x ^= lz;
        for (int u = 1, k = K; k --> 0; ) {
            int b = x >> k & 1;
            if (!at(u)[b]) {
                at(u)[b] = size();
                push_back({0, 0});
            }
            u = at(u)[b];
        }
    }
    void XOR(int v) { lz ^= v; }
    void fix(int u, int k) { if (lz >> k & 1) ::swap(at(u)[0], at(u)[1]); }
    int mg(int x, int y) {
        if (!x || !y) return x + y;
        for (int t : {0, 1}) at(x)[t] = mg(at(x)[t], at(y)[t]);
        return x;
    }
    void OR(int v, int x, int k) {
        if (!x || k < 0) return;
        fix(x, k);
        if (v >> k & 1) at(x)[1] = mg(at(x)[0], at(x)[1]), at(x)[0] = 0;
        for (int t : {0, 1}) OR(v, at(x)[t], k - 1);
    }
    void OR(int v) {
        OR(v, 1, K - 1);
        lz = 0;
    }
    void AND(int v) {
        lz ^= ~0;
        OR(~v);
        lz ^= ~0;
    }
    int mx() {
        int r = 0;
        for (int k = K, u = 1; k --> 0; ) {
            if (at(u)[1 ^ (lz >> k & 1)]) r ^= (1 << k), u = at(u)[1 ^ (lz >> k & 1)];
            else u = at(u)[lz >> k & 1];
        }
        return r;
    }
};

vector<int> v;
string s;

int nx() { int x = v.back(); v.pop_back(); return x; }
char eat() { char c = s.back(); s.pop_back(); return c; }

int ans = 0;
int parse();
int term() {
    switch (eat()) {
        case 'x': return nx();
        case '(': return parse();
        default: assert(false);
    }
}
int parse() {
    trie t;
    t.insert(0);
    int val = 0;
    bool init = 1;
    while (s.size()) {
        if (s.back() == ')') {
            eat();
            return val;
        }
        char op = (init ? 'Y' : eat());
        int v = term();
        switch (op) {
            case 'Y':
                t.XOR(v), val ^= v;
                break;
            case 'F':
                t.OR(v), val |= v;
                break;
            case 'W':
                t.AND(v), val &= v;
                break;
            default: assert(false);
        }
        t.insert(v);
        ans = max(ans, t.mx());
        init = 0;
    }
    return val;
}

int main() {
    int n; cin >> n;
    v.resize(n);
    for (int &x : v) cin >> x;
    reverse(v.begin(), v.end());
    cin >> s;
    reverse(s.begin(), s.end());
    parse();
    cout << ans << endl;
}
