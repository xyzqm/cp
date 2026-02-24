#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int m;

void ac(){
   int n; cin >> n;
   vector<int> a(n + 1);
   for(int i = 1; i <= n; i++) cin >> a[i];
   int ans = 0;
   for(int i = 2; i <= n; i++){
      int mn = min(a[i], a[i - 1]);
      a[i - 1] -= mn;
      a[i] -= mn;
      if(i + 1 <= n) a[i + 1] = max(0ll, a[i + 1] - mn);
      ans += mn;
   }
   for(int i = 1; i <= n; i++) ans += a[i];
   cout << ans << endl;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t >> m;
    // if (m > 1) {
    //     cout << "10\n1\n1 10\n12\n3\n2 1\n3 6\n1 5\n";
    // }
    while (t--) ac();
}
