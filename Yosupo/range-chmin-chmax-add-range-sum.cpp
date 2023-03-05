#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const LL INF = 1e16;

/*
 *  resource : "https://codeforces.com/blog/entry/57319"
 *  tested in "https://judge.yosupo.jp/submission/128706"
 *  
 * */
namespace segtree_beats {
    const int N = 2e5 + 5;
    LL mx[4 * N], mn[4 * N], smx[4 * N], smn[4 * N], sum[4 * N], add[4 * N];
    int mxcnt[4 * N], mncnt[4 * N];

    int L, R;

    void applyMax(int u, LL x) {
        sum[u] += mncnt[u] * (x - mn[u]);
        if(mx[u] == mn[u]) mx[u] = x;
        if(smx[u] == mn[u]) smx[u] = x;
        mn[u] = x;
    }
    void applyMin(int u, LL x) {
        sum[u] -= mxcnt[u] * (mx[u] - x);
        if(mn[u] == mx[u]) mn[u] = x;
        if(smn[u] == mx[u]) smn[u] = x;
        mx[u] = x;
    }
    void applyAdd(int u, LL x, int tl, int tr) {
        sum[u] += (tr - tl + 1) * x;
        add[u] += x;
        mx[u] += x, mn[u] += x;
        if(smx[u] != -INF) smx[u] += x;
        if(smn[u] != INF) smn[u] += x;
    }    
    void push(int u, int tl, int tr){
        int lft = u << 1, ryt = lft | 1, mid = tl + tr >> 1;
        if(add[u] != 0){
            applyAdd(lft, add[u], tl, mid);
            applyAdd(ryt, add[u], mid + 1, tr);
            add[u] = 0;
        }
        if(mx[u] < mx[lft]) applyMin(lft, mx[u]);
        if(mx[u] < mx[ryt]) applyMin(ryt, mx[u]);

        if(mn[u] > mn[lft]) applyMax(lft, mn[u]);
        if(mn[u] > mn[ryt]) applyMax(ryt, mn[u]);

    }
    void merge(int u) {
        int lft = u << 1, ryt = lft | 1;
        sum[u] = sum[lft] + sum[ryt];

        mx[u] = max(mx[lft], mx[ryt]);
        smx[u] = max(smx[lft], smx[ryt]);
        if(mx[lft] != mx[ryt]) smx[u] = max(smx[u], min(mx[lft], mx[ryt]));
        mxcnt[u] = (mx[u] == mx[lft]) * mxcnt[lft] + (mx[u] == mx[ryt]) * mxcnt[ryt];

        mn[u] = min(mn[lft], mn[ryt]);
        smn[u] = min(smn[lft], smn[ryt]);
        if(mn[lft] != mn[ryt]) smn[u] = min(smn[u], max(mn[lft], mn[ryt]));
        mncnt[u] = (mn[u] == mn[lft]) * mncnt[lft] + (mn[u] == mn[ryt]) * mncnt[ryt];
    }
    void minimize(int l, int r, LL x, int tl = L, int tr = R, int u = 1) {
        if(l > tr or tl > r or mx[u] <= x) return;
        if(l <= tl and tr <= r and smx[u] < x) {
            applyMin(u, x);
            return;
        }
        push(u, tl, tr);
        int mid = tl + tr >> 1, lft = u << 1, ryt = lft | 1;
        minimize(l, r, x, tl, mid, lft);
        minimize(l, r, x, mid + 1, tr, ryt);
        merge(u);
    }
    void maximize(int l, int r, LL x, int tl = L, int tr = R, int u = 1) {
        if(l > tr or tl > r or mn[u] >= x) return;
        if(l <= tl and tr <= r and smn[u] > x) {
            applyMax(u, x);
            return;
        }
        push(u, tl, tr);
        int mid = tl + tr >> 1, lft = u << 1, ryt = lft | 1;
        maximize(l, r, x, tl, mid, lft);
        maximize(l, r, x, mid + 1, tr, ryt);
        merge(u);
    }
    void increase(int l, int r, LL x, int tl = L, int tr = R, int u = 1) {
        if(l > tr or tl > r) return;
        if(l <= tl and tr <= r) {
            applyAdd(u, x, tl, tr);
            return;
        }
        push(u, tl, tr);
        int mid = tl + tr >> 1, lft = u << 1, ryt = lft | 1;
        increase(l, r, x, tl, mid, lft);
        increase(l, r, x, mid + 1, tr, ryt);
        merge(u);
    }
    LL getSum(int l, int r, int tl = L, int tr = R, int u = 1) {
        if(l > tr or tl > r) return 0;
        if(l <= tl and tr <= r) return sum[u];
        push(u, tl, tr);
        int mid = tl + tr >> 1, lft = u << 1, ryt = lft | 1;
        return getSum(l, r, tl, mid, lft) + getSum(l, r, mid + 1, tr, ryt);
    } 
    void build(LL a[], int tl = L, int tr = R, int u = 1) {
        if(tl == tr) {
            sum[u] = mn[u] = mx[u] = a[tl];
            mxcnt[u] = mncnt[u] = 1;
            smx[u] = -INF;
            smn[u] = INF;
            return;
        }
        int mid = tl + tr >> 1, lft = u << 1, ryt = lft | 1;
        build(a, tl, mid, lft);
        build(a, mid + 1, tr, ryt);
        merge(u);
    }
    void init(LL a[], int _L, int _R) {
        L = _L, R = _R;
        build(a);
    }
}
LL a[200005];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++) cin >> a[i];
    segtree_beats :: init(a, 0, n - 1);
    while(q--) {
        int t, l, r;
        cin >> t >> l >> r;
        LL x;
        if(t != 3) cin >> x;
        if(t == 0) segtree_beats :: minimize(l, r - 1, x);
        else if(t == 1) segtree_beats :: maximize(l, r - 1, x);
        else if(t == 2) segtree_beats :: increase(l, r - 1, x);
        else cout << segtree_beats :: getSum(l, r - 1) << '\n';
    }
}
