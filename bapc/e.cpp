#include <bits/stdc++.h>
#define int64_t
using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> b(n);
  for (int i = 0;i<n;i++){
    cin >> a[i];
  }
  for (int i = 0;i<n;i++){
    cin >> b[i];
  }
  bool allSame = true;
  for (int i = 0;i<n;i++){
    if (a[i]!=b[i]){
      allSame=false;
      break;
    }
  }
  if (allSame){
    cout << "YES\n";
    return;
  }

  int numOddDiff =0;
  for (int i=0;i<n;i++){
    if ((b[i]-a[i])%2==1){
      numOddDiff++;
    }
  }

  int numOddA = 0;
  int numEvenA = 0;
  for (int i = 0;i<n;i++){
    if (a[i] %2==0){
      numEvenA++;
    } else {
      numOddA++;
    }
  }

  if (numEvenA %2==1 && numOddA%2 == 0){
    //no operations possible, giveup
    cout << "NO\n";
  } else if (numEvenA%2==1 && numOddA%2==1) {
    if (numOddDiff == 1) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  } else if (numEvenA%2==0&&numOddA%2==0) {
    if (numOddDiff==0) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  } else {
    if (numOddDiff <= 1) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
}

int32_t main() {
  int t;
  cin >> t;
  for (int i=0;i<t;i++) {
    solve();
  }
}