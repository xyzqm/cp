#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;
int n;
int a[N];
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    // ans = {4, 2, 2, 4} => RRRRLLRRLLLL
    // ans = {a, b, c, d} => a Rs, b Ls, c Rs, d Ls, ...
    vector<int> ans;
    /*
    Let's visualize {4, 2, 2, 4} like so:
    --->--->--->--->
            <---<---
            --->--->
    <---<---<---<---
     0.5 1.5 2.5 3.5
    prev contains the "levels" (rows) of the leftmost arrows ({0, 3} in this case)      
    */
    vector<int> prev;
    /*
    Algorithm: process the points from back to front
    Motivation: 
    The sequence for crossing a single point j times is trivial (j/2 RLs).
    In the above visualization of {4, 2, 2, 4}, we can see this sequence by isolating the rightmost column.
    In addition, notice any suffix of the columns is a valid solution.
    i.e. taking the last two columns and shifting the 2.5 to a 0.5 is an optimal solution.
    This motivates an approach where we gradually extend the suffix from n.5 --> 0.5.
    */
    for (int i = n - 1; i >= 0; i--) {
        if (i == n - 1) { // initializing the last "column" (as explained above)
            for (int j = 0; j < a[i]; j++) {
                ans.push_back(1);
                prev.push_back(j); // all "arrows" are leftmost, push them all into prev
            }
        }
        else {
            int j;
            /* 
            Example
            Current suffix:
            --->--->--->
                <---<---
                --->--->
            <---<---<---
            --->--->--->
            <---<---<---
            ans: {3, 2, 2, 3, 3, 3}, prev: {0, 3, 4, 5}, a[i]: 2
            Desired extended suffix:
            --->--->--->--->
                    <---<---
                    --->--->
                <---<---<---
                --->--->--->
            <---<---<---<---
            */
           // in total, we have to append a[i] arrows (R or L) to the front of the sequence
            for (j = 0; j < a[i] - 1; j++) {
                // we only add a[i] - 1 arrows here to save an arrow to append to the last row
                if (j >= prev.size()) break;
                ans[prev[j]]++; // extending the longest segments
            }
            if (j < prev.size()) { // didn't extend every segment -> skip to the last one
                ans.back()++;
                while (prev.size() > j) prev.pop_back();
                prev.push_back(ans.size() - 1);
                j++; 
            }
            while (j < a[i]) {
                ans.push_back(1);
                prev.push_back(ans.size() - 1);
                j++;
            }
        }
    }
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i]; j++) {
            if (i % 2 == 0) cout << 'R';
            else cout << 'L';
        }
    }
}