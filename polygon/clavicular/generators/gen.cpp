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
        int k = rnd.next(1, N);
        int x = rnd.next(1, N / k);
        cout << N << " " << k << " " << x << endl;
        for (int i = 1; i <= N; i++) {
            cout << rnd.next(1, k) << " \n"[i == N];
        }
    }
    return 0;
}
