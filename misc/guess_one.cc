#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int query(string s) {
   cout << 1 << " " << s << endl;
   int x; cin >> x;
   return x;
}

void ac() {
    int n; cin >> n;
    int ones = query("1");
    int oi = query("01");
    int ii = query("11");
    cout << "0 1 " << (ones != oi + ii) << endl;
    int v; cin >> v;
}

int32_t main() {
    // cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
