#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve()
{
    int n, m, l, q; cin >> n >> m >> l >> q;
    swap(n, m);

    vector <int> a(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }

    // lines : {a[i], -i}
    // a[i] - i * slope

    vector <int> ans(q), got(q, INF);
    vector <array<int, 4>> qq;
    vector <int> a1(q), a2(q), a3(q);

    for (int i = 0; i < q; i++){
        int slope, x; cin >> slope >> x;

        int L, R;

        {
            int lo = 1, hi = n + 1;
            while (lo != hi){
                int mid = (lo + hi) / 2;
                if (a[mid] + l > x){
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }

            L = lo;
        }

        {
            int lo = L - 1, hi = n;
            while (lo < hi){
                int mid = (lo + hi + 1) / 2;
                if (a[mid] <= x){
                    lo = mid;
                } else {
                    hi = mid - 1;
                }
            }

            R = lo;
        }

        if (L > n || L > R){
            ans[i] = 0;
            continue;
        }

        ans[i] = R - L + 1;
        // ans = min(ans, (mn + l - x) / slope + R);
        qq.push_back({slope, L, R, i});
        a1[i] = l - x;
        a2[i] = slope;
        a3[i] = R;
    }

    auto useless = [&](int i1, int i2, int i3){
        assert(i1 < i2 && i2 < i3);
        // at less slope, i1 is likely to become better
        // at more slope, i3 is likely to be better
        // a[i] - i * s = a[j] - j * s
        // s (i - j) = a[i] - a[j]
        // s = a[i] - a[j] / (i - j)

        return (a[i2] - a[i1]) * (i3 - i2) >= (a[i3] - a[i2]) * (i2 - i1);
    };

    auto eval = [&](int i, int slope){
        // a[i] - i * slope
        return a[i] - i * slope;
    };

    auto dnc = [&](auto self, int l, int r, vector <array<int, 4>> qq) -> vector <int>{
        vector <int> st;
        vector <array<int, 4>> lq, rq, aq;
        int mid = (l + r) / 2;

        for (auto [slope, ql, qr, i] : qq){
            if (ql <= l && r <= qr){
                aq.push_back({slope, ql, qr, i});
            } else {
                if (ql <= mid){
                    lq.push_back({slope, ql, qr, i});
                }
                if (qr > mid){
                    rq.push_back({slope, ql, qr, i});
                }
            }
        }

        if (l == r){
            st.push_back(l);
        } else {
            st = self(self, l, mid, lq);
            auto rs = self(self, mid + 1, r, rq);

            for (auto x : rs){
                int sz = st.size();

                while (sz >= 2 && useless(st[sz - 2], st[sz - 1], x)){
                    st.pop_back();
                    sz -= 1;
                }

                st.push_back(x);
            }
        }

        int ptr = 0;
        for (auto [slope, ql, qr, i] : aq){
            while (ptr + 1 < st.size() && eval(st[ptr + 1], slope) <= eval(st[ptr], slope)){
                ptr++;
            }

            got[i] = min(got[i], eval(st[ptr], slope));
        }
        return st;
    };

    sort(qq.begin(), qq.end());

    dnc(dnc, 1, n, qq);

    auto get = [&](int x, int y){
        int z = x / y;
        if (z * y > x) z--;
        return z;
    };

    for (int i = 0; i < q; i++) if (ans[i] != 0){
        ans[i] = min(ans[i], get((got[i] + a1[i]), a2[i]) + a3[i]);
    }

    for (auto x : ans){
        cout << x << "\n";
    }
}

int32_t main()
{
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // freopen("in",  "r", stdin);
    // freopen("out", "w", stdout);

  //  cin >> t;
    for(int i = 1; i <= t; i++)
    {
        //cout << "Case #" << i << ": ";
        Solve();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    // cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
    return 0;
}
