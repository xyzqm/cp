#include "testlib.h"
using namespace std;

// inf - stream with the testdata.

int main(int argc, char *argv[])
{
    registerValidation(argc, argv);
    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();
    int tot = 0;
    for (int i = 0; i < t; i++) {
        setTestCase(i + 1);
        string s = inf.readString();
        tot += s.size();
    }
    ensure(tot <= 200000);
    inf.readEof();
    return 0;
}
