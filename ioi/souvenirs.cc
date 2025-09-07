#include <bits/stdc++.h>
using namespace std;


#ifdef ONLINE_JUDGE
#include "souvenirs.h"
#else
pair<vector<int32_t>, int> transaction(int M);
#endif

#define int long long

void buy_souvenirs(int32_t N, int P0) {
    vector<int> P(N, -1), frq(N, 0);
    P[0] = P0;
    auto my_transaction = [&](int M) {
        auto [eq, sum] = transaction(M);
        for (int x : eq) ++frq[x];
        return make_pair(eq, M - sum);
    };
    auto solve = [&](this auto solve, pair<vector<int32_t>, int> data) -> void {
        auto [eq, sum] = data;
        int i = eq[0];
        if (P[i] >= 0) return;
        while (1) {
            while (P[eq.back()] >= 0) sum -= P[eq.back()], eq.pop_back();
            if (eq.size() > 1) solve(my_transaction(sum / eq.size()));
            else break;
        }
        P[i] = sum;
        if (i + 1 < N && P[i + 1] < 0) solve(my_transaction(sum - 1));
    };
    solve(my_transaction(P0 - 1));
    for (int i = 1; i < N; i++) while (frq[i] < i) my_transaction(P[i]);
}
