#include <bits/stdc++.h>
using namespace std;

#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

int cnt_k_good(const std::vector<int>& a, int k) {
    int rt = k - 1, tot = 0; // rightmost possible point
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] == k) tot += rt <= i;
        else rt = max(rt, i + k - a[i]);
    }
    return tot;
}

vector<int> ac() {
    int n, k, x; cin >> n >> k >> x;
    vector<int> vals(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> vals[i];
    }
    ranges::sort(vals);
    vector<int> rt(n + 1);
    int fst = rt[0] = k; // first ending index
    for (int i = 1; i <= n; i++) {
        if (vals[i] < k) fst = max(fst, i + k - vals[i]);
        rt[i] = fst;
    }
    int non_ks = min(fst - 1, n);
    DBG(vals);
    DBG(rt);
    for (int i = non_ks, lst = vals.size(); i > 0 && lst - rt[i] > x; i--) { // lst = one idx after position of last undeleted k
        if (vals[i] == k) continue;
        int del = max((int)0, k - vals[i] - 1);
        if (lst - del - 1 - rt[i - 1] >= x) {
            swap(vals[i], vals[lst - 1 - del]);
            lst -= del + 1;
        }
        else {
            int j = i;
            DBG(j);
            while (lst - rt[i] > x) {
                j++;
                rt[i] = max(rt[i], j + k - vals[i]);
            }
            assert(lst - rt[i] == x);
            swap(vals[i], vals[j]);
            break;
        }
    }
    DBG(vals);
    DBG(ks);
    vals.erase(vals.begin());
    if (cnt_k_good(vals, k) != x) return {0};
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
