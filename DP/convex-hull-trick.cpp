#include <bits/stdc++.h>
using namespace std;
using LL = long long;
// SPOJ - APIO10A 
struct line {
    LL m, c;
    line() {}
    line(LL m, LL c) : m(m), c(c) {}
};
struct convex_huLL_trick {
    vector<line> lines;
    int ptr = 0;
    convex_huLL_trick() {}
    bool bad(line a, line b, line c) {
        return 1.0 * (c.c - a.c) * (a.m - b.m) <
               1.0 * (b.c - a.c) * (a.m - c.m);
    }
    void add(line L) {
        int sz = lines.size();
        while (sz >= 2 && bad(lines[sz - 2], lines[sz - 1], L)) {
            lines.pop_back();
            sz--;
        }
        lines.push_back(L);
    }
    LL get(int idx, int x) { return (1LL * lines[idx].m * x + lines[idx].c); }
    LL query(int x) {
        if (lines.empty()) return 0;
        if (ptr >= lines.size()) ptr = lines.size() - 1;
        while (ptr < lines.size() - 1 && get(ptr, x) > get(ptr + 1, x)) ptr++;
        return get(ptr, x);
    }
};
const int MAX = 1e6 + 5;
LL dp[MAX], x[MAX], sum[MAX];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        LL a, b, c;
        cin >> a >> b >> c;
        for(int i = 1; i <= n; i++) {
            cin >> x[i];
            sum[i] = x[i] + sum[i - 1];
        }
        convex_huLL_trick CHT;
        CHT.add(line(0, 0));
        for(int i  = 1; i <= n; i++) {
            dp[i] = a * sum[i] * sum[i] + b * sum[i] + c - CHT.query(sum[i]);
            CHT.add(line(2 * a * sum[i], -a * sum[i] * sum[i] + b * sum[i] - dp[i]));
        }
        cout << dp[n] << '\n';
    }
    return 0;
}
