#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int TEST_CASES = 1;
const int FIXED_N = 200000;
const int Q = 1000000;
const int P = 10;
const int LEN = 2;
// total runtime: 26^2 * TC * N + TC * Q * LEN + TC * N * P
// brute: Q * TC * N
/* const int MAX_TOTAL_T_LEN = 2000000; */

/* string generate_random_string(int length) { */
/*     string s; */
/*     for (int i = 0; i < length; i++) { */
/*         s += rnd.next("a", "z"); */
/*     } */
/*     return s; */
/* } */

vector<string> generate_queries(const string &s, int q) {
    vector<string> queries;
    for (int i = 0; i < q - P; i++) {
        // Generate a sorted string of some characters from s
        string subset;
        set<char> chosen;
        int len = rnd.next(1, LEN);
        while (len--) {
            char c = s[rnd.next(0, (int)s.size() - 1)];
            chosen.insert(c);
        }
        subset.assign(chosen.begin(), chosen.end());
        queries.push_back(subset);
    }
    for (int i = 0; i < P; i++) {
        int j = rnd.next(0, 1000);
        queries.insert(queries.begin() + j, "?");
    }
    return queries;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int t = TEST_CASES;
    cout << t << "\n";
    
    int total_t_len = 0;
    for (int i = 0; i < t; i++) {
        string s = rnd.next("[a-z]{200000}");
        cout << s << "\n";
        
        cout << Q << "\n";
        
        vector<string> queries = generate_queries(s, Q);
        for (const string &query : queries) {
            cout << query << "\n";
        }
    }
    
    return 0;
}
