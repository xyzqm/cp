#include <iostream>
using namespace std;
char c[3][3];
char row(int i) {
    char f = c[i][0];
    if (f == '.') return 0;
    for (int j = 1; j < 3; j++) {
        if (c[i][j] != f) return 0;
    }
    return f;
}
char col(int i) {
    char f = c[0][i];
    if (f == '.') return 0;
    for (int j = 1; j < 3; j++) {
        if (c[j][i] != f) return 0;
    }
    return f;
}
char d1() {
    char f = c[0][0];
    if (f == '.') return 0;
    for (int i = 1; i < 3; i++) if (c[i][i] != f) return 0;
    return f;
}
char d2() {
    char f = c[0][2];
    if (f == '.') return 0;
    for (int i = 1; i < 3; i++) if (c[i][2 - i] != f) return 0;
    return f;
}
int main() {
    int t; cin >> t;
    while (t--) {
        for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) cin >> c[i][j];
        bool won = false;
        for (int i = 0; i < 3; i++) {
            char a = row(i), b = col(i);
            if (a) cout << a << endl;
            else if (b) cout << b << endl;
            if ((won = (a || b))) break;
        }
        if (won) continue;
        char e = d1(), f = d2();
        if (e) cout << e << endl;
        else if (f) cout << f << endl;
        else cout << "DRAW" << endl;
    }
}