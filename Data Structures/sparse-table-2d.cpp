#include <bits/stdc++.h>
using namespace std;
using LL = long long;
namespace st2 {
    const int N = 2e3 + 5, B = 12;
    using Ti = long long;
    Ti Id = LLONG_MAX;
    Ti f(Ti a, Ti b) {
        return max(a, b);
    }
    Ti tbl[N][N][B];
    void init(int n, int m) {
        for(int k = 1; k < B; k++) {
            for(int i = 0; i + (1 << k) - 1 < n; i++) {
                for(int j = 0; j + (1 << k) - 1 < m; j++) {
                    tbl[i][j][k] = tbl[i][j][k - 1];
                    tbl[i][j][k] = f(tbl[i][j][k], tbl[i][j + (1 << k - 1)][k - 1]);
                    tbl[i][j][k] = f(tbl[i][j][k], tbl[i + (1 << k - 1)][j][k - 1]);
                    tbl[i][j][k] = f(tbl[i][j][k], tbl[i + (1 << k - 1)][j + (1 << k - 1)][k - 1]);
                }
            }
        }
    }
    Ti query(int i, int j, int len) {
        int k = __lg(len);
        LL ret = tbl[i][j][k];
        ret = f(ret, tbl[i + len - (1 << k)][j][k]);
        ret = f(ret, tbl[i][j + len - (1 << k)][k]);
        ret = f(ret, tbl[i + len - (1 << k)][j + len - (1 << k)][k]);
        return ret;
    }
}
int main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> st2 :: tbl[i][j][0];
    st2 :: init(n, m);
    cout << st2 :: query(1, 1, 3);
}
