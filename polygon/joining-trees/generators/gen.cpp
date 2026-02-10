#include "testlib.h"
#include <cassert>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int N = opt<int>(1);
    int t = min(500000 / N, 10000);
    // int t = opt<int>(1); // number of test cases
    cout << t << "\n";

    while (t--) {
        cout << N << endl;
        for (int i = 2; i <= N; i++) {
            int rng = rnd.next(1, 1000);
            if (rng == 1) cout << -1 << " \n"[i == N];
            else cout << rnd.next(1, i - 1) << " \n"[i == N];
        }
    }
    return 0;
}
