#include<bits/stdc++.h>
using namespace std;
using LL = long long;
const int K = 805, N = 4005;
LL dp[2][N], _cost[N][N];
// 1-indexed for convenience
LL cost(int l, int r) {
    return _cost[r][r] - _cost[l - 1][r] - _cost[r][l - 1] + _cost[l - 1][l - 1] >> 1;
}
void compute(int cnt, int l, int r, int optl, int optr) {
    if(l > r) return;
    int mid = l + r >> 1;
    LL best = INT_MAX;
    int opt = -1;
    for(int i = optl; i <= min(mid, optr); i++) {
        LL cur = dp[cnt ^ 1][i - 1] + cost(i, mid);
        if(cur < best) best = cur, opt = i;
    }
    dp[cnt][mid] = best;
    compute(cnt, l, mid - 1, optl, opt);
    compute(cnt, mid + 1, r, opt, optr);
}
LL dnc_dp(int k, int n) {
    fill(dp[0] + 1, dp[0] + n + 1, INT_MAX);
    for(int cnt = 1; cnt <= k; cnt++) {
        compute(cnt & 1, 1, n, 1, n);
    }
    return dp[k & 1][n];
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> _cost[i][j];
            _cost[i][j] += _cost[i - 1][j] + _cost[i][j - 1] - _cost[i - 1][j - 1];
        }
    }
    cout << dnc_dp(k, n) << '\n';
    return 0;
}
