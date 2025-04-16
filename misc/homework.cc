#include <bits/stdc++.h>
using namespace std;

const int N = 4e6 + 1;

array<int, 2> c[N];

string expr;
int id = 0, idx = 0, t[N]; // 0 = min, 1 = max, 2 = ?
int l[N], r[N], sz[N];
int parse() {
    int cur = id++;
    if (expr[idx] == 'm') {
        t[cur] = (expr[++idx] == 'a');
        assert(expr[idx += 2] == '(');
        ++idx;
        sz[cur] += sz[c[cur][0] = parse()];
        assert(expr[idx++] == ',');
        sz[cur] += sz[c[cur][1] = parse()];
        assert(expr[idx++] == ')');
        if (t[cur]) { // max
            l[cur] = l[c[cur][0]] + l[c[cur][1]];
            for (int t : {0, 1}) r[cur] = max(r[cur], sz[c[cur][t]] + r[c[cur][t ^ 1]]);
        }
        else { // min
           l[cur] = min(l[c[cur][0]], l[c[cur][1]]);
           r[cur] = r[c[cur][0]] + r[c[cur][1]] - 1;
        }
    }
    else t[cur] = 2, sz[cur] = l[cur] = r[cur] = 1, idx++;
    return cur;
}

void print(int x) {
    if (t[x] < 2) {
        cout << (t[x] ? "max" : "min") << "(";
        print(c[x][0]);
        cout << ",";
        print(c[x][1]);
        cout << ")";
    }
    else cout << "?";
}

int main() {
    cin >> expr;
    int rt = parse();
    // print(rt);
    // cout << endl;
    cout << r[rt] - l[rt] + 1 << endl;
}
