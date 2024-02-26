#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1e5;
int n, a[N];
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, zeros = 0;
        cin >> n;
        vector<int> v;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (i) {
                if (a[i] - a[i - 1]) v.push_back(a[i] - a[i - 1]);
                else ++zeros;
            }
        }
        while (v.size() > 1) {
            sort(v.begin(), v.end());
            vector<int> nv;
            int nz = 0;
            for (int i = 0; i < v.size(); i++) {
                if (!i && zeros) {
                    nv.push_back(v[i]);
                    continue;
                } else if (i) {
                    if (v[i] - v[i - 1]) nv.push_back(v[i] - v[i - 1]);
                    else ++nz;
                }
            }
            if (zeros) --zeros;
            zeros += nz;
            v = nv;
        }
        if (!v.size()) cout << 0 << endl;
        else cout << v[0] << endl;
    }
}