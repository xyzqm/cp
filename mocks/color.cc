#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

const int M = 1e9 + 7;
int inv(int x) {
    int r = 1;
    for (int xp = M - 2; xp; xp >>= 1, x = x * x % M) if (xp & 1) r = r * x % M;
    return r;
}

void ad(int &a, int b) { if ((a += b) >= M) a -= M; }

map<vector<int>, int> parts;

vector<vector<int>> partitions(int mn, int n) {
    if (!n) return {{}};
    else {
        vector<vector<int>> res;
        for (int cur = mn; cur <= n; cur++) {
            auto nx = partitions(cur, n - cur);
            for (auto &v : nx) {
                v.insert(v.begin(), cur);
                res.push_back(v);
            }
        }
        return res;
    }
}

vector<int> mod(vector<int> v, int i, int j) {
    ++v[i], --v[j];
    sort(v.begin(), v.end());
    v.erase(remove(v.begin(), v.end(), 0), v.end());
    return v;
}

const int P = 42;
using mat = array<array<int, P>, P>;

mat operator*(mat a, mat b) {
    mat c{};
    for (int i = 0; i < P; i++) {
        for (int k = 0; k < P; k++) {
            for (int j = 0; j < P; j++) {
                ad(c[i][j], a[i][k] * b[k][j] % M);
            }
        }
    }
    return c;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, t, k; cin >> n >> t >> k;
    int denom = inv(n * n);
    for (auto &partition: partitions(1, n)) parts[partition] = parts.size();
    DBG(parts);
    mat mtx{};
    for (auto &[partition, idx] : parts) {
        for (int i = 0; i < partition.size(); i++) {
            for (int j = 0; j < partition.size(); j++) {
                ad(mtx[idx][parts[mod(partition, i, j)]], partition[i] * partition[j] * denom % M);
            }
        }
    }
    DBG(mtx);
    mat res = mtx;
    for (--t; t; t >>= 1, mtx = mtx * mtx) if (t & 1) res = res * mtx;
    int p = 0;
    for (auto &[partition, idx] : parts) if (partition.size() >= k) ad(p, res[0][idx]);
    cout << p << "\n";
}
