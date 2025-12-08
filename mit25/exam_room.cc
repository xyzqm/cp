#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

struct vec{
    int x, y;
    vec(){}
    vec(int x, int y): x(x), y(y){}
};

vec operator+(vec a, vec b) {
    return {a.x + b.x, a.y + b.y};
}

vec operator-(vec a, vec b) {
    return {a.x - b.x, a.y - b.y};
}

int mag(vec v) { return v.x * v.x  + v.y * v.y; }

int operator%(vec a, vec b){
    return a.x * b.y - a.y * b.x;
}
int operator*(const vec &a, const vec &b){
    return a.x * b.x + a.y * b.y;
}

const vec u(0, 1);

bool A(const vec &p){
    return u % p > 0 || (u % p == 0 && u * p > 0);
}

bool operator<(const vec &a, const vec &b){
    return (A(a) == A(b) && a % b > 0) || (A(a) && !A(b));
}

const int M = 998244353;

void ad(int &a, int b) { a = (a + b) % M; }

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<vec> v(n);
    for (auto &[x, y] : v) cin >> x >> y;
    sort(v.begin(), v.end());
    int ans = n;
    for (int i = 0; i < n; i++) { // count # of ways starting with piece i
        vector<int> ws(n);
        ws[i] = 1;
        for (int j = i; j < n; j++) {
            for (int k = i; k < j; k++) if (max(mag(v[j]), mag(v[k])) < mag(v[j] - v[k])) {
                ad(ws[j], ws[k]);
            }
            if (max(mag(v[i]), mag(v[j])) < mag(v[i] - v[j])) ad(ans, ws[j]);
        }
    }
    cout << ans << endl;
}
