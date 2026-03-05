#include "testlib.h"
using namespace std;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();
    int total_n = 0;

    for (int test = 0; test < t; ++test) {
        setTestCase(test + 1);

        int n = inf.readInt(2, 500000, "n");
        inf.readSpace();
        int k = inf.readInt(1, n, "k");
        inf.readSpace();
        int x = inf.readInt(0, n, "x");
        inf.readEoln();
        total_n += n;

        for (int i = 0; i < n; ++i) {
            inf.readInt(1, k, "a[i]");
            if (i + 1 < n) inf.readSpace();
        }
        inf.readEoln();
    }

    ensure(total_n <= 500000);
    inf.readEof();
}
