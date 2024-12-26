#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 1;

int n, a[N], lc[N], rc[N], l[N], r[N], eq[N], s[N], sz[N];

void dnq(int x, bool lp, bool rp) {
    if (lc[x]) dnq(lc[x], lp, true);
    if (rc[x]) dnq(rc[x], true, rp);
    sz[x] = sz[lc[x]] + sz[rc[x]] + 1;
    l[x] = l[lc[x]] + eq[lc[x]];
    r[x] = r[rc[x]] + eq[rc[x]];
    eq[x] = r[lc[x]] + l[rc[x]] + 1;
    if (!lp) eq[x] += l[x], l[x] = 0;
    if (!rp) eq[x] += r[x], r[x] = 0;
    s[x] = s[lc[x]] + s[rc[x]] + eq[x];
}

void push(int x, int v) {
    int dl = s[lc[x]] + l[lc[x]];
    int dr = s[rc[x]] + r[rc[x]];
    if (lc[x]) push(lc[x], v + s[rc[x]] + sz[rc[x]] + 1);
    cout << v + dl + dr << " ";
    if (rc[x]) push(rc[x], v + s[lc[x]] + sz[lc[x]] + 1);
}

signed main() {
    cin >> n;
    // create cartesian tree
    vector<int> st;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        while (st.size() && a[i] > a[st.back()]) {
            lc[i] = st.back();
            st.pop_back();
        }
        if (st.size()) rc[st.back()] = i;
        st.push_back(i);
    }
    dnq(st[0], false, false);
    push(st[0], 0);
    cout << endl;
}
