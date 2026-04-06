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
    int n; cin >> n;
    string s = "His";
    while (n--) s += 's';
    cout << s << "!\n";
}
