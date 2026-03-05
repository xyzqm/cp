#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

vector<int> ac() {
    int n, k, x; cin >> n >> k >> x;
    int ks = 0, non_ks = 0; vector<int> vals(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> vals[i];
        if (vals[i] == k) ++ks;
        else ++non_ks;
    }
    ranges::sort(vals);
    vector<int> rt(n + 1);
    int fst = rt[0] = k; // first ending index
    for (int i = 1; i <= n; i++) {
        if (vals[i] < k) fst = max(fst, i + k - vals[i]);
        rt[i] = fst;
    }
    non_ks = fst - 1;
    ks = n - non_ks;
    if (ks < x) return {0};
    DBG(vals);
    // DBG(ks);
    DBG(rt);
    for (int i = non_ks, lst = vals.size(); i > 0 && lst - rt[i] > x; i--) { // lst = one idx after position of last undeleted k
        int del = max((int)0, k - vals[i] - 1);
        if (lst - del - 1 - rt[i - 1] >= x) {
            swap(vals[i], vals[lst - 1 - del]);
            lst -= del + 1;
            ks = lst - rt[i - 1];
        }
        else {
            int j = i;
            while (lst - rt[i] > x) {
                j++;
                rt[i] = max(rt[i], j + k - vals[i]);
            }
            assert(lst - rt[i] == x);
            ks = x;
            swap(vals[i], vals[j]);
            break;
        }
        DBG(vals);
    }
    DBG(vals);
    vals.erase(vals.begin());
    if (ks > x) return {0};
    else return vals;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) {
        for (int v : ac()) cout << v << " ";
        cout << "\n";
    }
}
