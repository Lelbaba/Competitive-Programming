#include<bits/stdc++.h>
using namespace std;
using LL = long long;
// SPOJ BRKSTRING
const int N = 1005;
LL dp[N][N], a[N];
int opt[N][N];
LL cost(int i, int j) {
    return a[j + 1] - a[i];
}
LL knuth_optimization(int n) {
    for(int i = 0; i < n; i++) {
        dp[i][i] = 0;
        opt[i][i] = i;
    }
    for(int i = n - 2; i >= 0; i--) {
        for(int j = i + 1; j < n; j++) {
            LL mn = LLONG_MAX;
            LL c = cost(i, j);
            for(int k = opt[i][j - 1]; k <= min(j-1, opt[i + 1][j]); k++) {
                if(mn > dp[i][k] + dp[k + 1][j] + c) {
                    mn = dp[i][k] + dp[k + 1][j] + c;
                    opt[i][j] = k;
                }
            }
            dp[i][j] = mn;
        }
    }
    return dp[0][n - 1];
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int m, n;
    while(cin >> m >> n) {
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        a[0] = 0, a[n + 1] = m;
        cout << knuth_optimization(n + 1) << '\n';
    }
    
    return 0;
}
