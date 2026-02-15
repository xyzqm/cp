#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int rem(int a, int b) {
    string sa = to_string(a), sb = to_string(b);
    for (int i = 0; i < sa.size(); i++) {
        if (sa[i] != '1') break;
        if (i + 1 == sa.size()) {
           if (!b) return i + 1;
        }
        else if (stoll(sa.substr(i + 1)) == b) return i + 1;
    }
    return 0;
}

void ac() {
    int a, b, k; cin >> a >> b >> k;
    if (a == b) cout << "Yes\n0\n";
    else if (!k) cout << "No\n";
    else if (b > a && (b - a) % 9 == 0) { // 1 operation
        cout << "Yes\n1\n1 " << (b - a) / 9 << "\n";
    }
    else if (rem(a, b)) cout << "Yes\n1\n2 " << rem(a, b) << "\n";
    else if (k < 2) cout << "No\n";
    else { // always doable within two operations
        int rem = (b - a) % 9;
        if (rem < 0) rem += 9;
        DBG(rem);
        assert(rem < 9);
        string sa = to_string(a), sb = to_string(b);
        reverse(sa.begin(), sa.end());
        reverse(sb.begin(), sb.end());
        while (sb.size() < sa.size()) sb.push_back('0');
        while (rem < 9) sb.push_back('1'), ++rem;
        reverse(sb.begin(), sb.end());
        int c = stoll(sb);
        DBG(c);
        assert(c > a && (c - a) % 9 == 0);
        cout << "Yes\n2\n";
        cout << "1 " << (c - a) / 9 << "\n";
        cout << "2 " << ::rem(c, b) << "\n";
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
