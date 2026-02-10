
#include "testlib.h"
using namespace std;

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);
    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();
    int tot = 0;
    for (int i = 0; i < t; i++) {
        setTestCase(i + 1);
        int n = inf.readInt(2, 500000, "n");
        inf.readEoln();
        tot += n;
        for (int j = 2; j <= n; j++) {
            int v = inf.readInt(-1, j - 1);
            ensure(v != 0);
            if (j < n) inf.readSpace();
        }
        inf.readEoln();
    }
    ensure(tot <= 500000);
    inf.readEof();
    return 0;
}
