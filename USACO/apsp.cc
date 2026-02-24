#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

using vec = array<int, 3>;

array<vec, 12> dirs = {{
    {0, 0, 0},
    {0, -1, 0},
    {0, -2, 0},
    {-1, -2, 0},
    {-2, -2, 0},
}};

void ac() {

}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}
