#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string s; cin >> s;
    map<char, int> bal;
    map<char, char> lf;
    lf['>'] = '<';
    lf['}'] = '{';
    lf[']'] = '[';
    lf[')'] = '(';
    int ans = 0;
    stack<char> open;
    for (char c : s) {
        if (string("<{[(").contains(c)) open.push(c);
        else if (!open.size()) {
            cout << "Impossible\n";
            return 0;
        }
        else {
            if (open.top() != lf[c]) ++ans;
            open.pop();
        }
    }
    cout << (open.size() ? "Impossible" : to_string(ans)) << "\n";
}
