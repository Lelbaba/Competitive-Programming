#include <bits/stdc++.h>
using namespace std;
using LL = long long;

/*....................................................................*/ 
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
// Order Statistic Tree

/* Special functions:
        find_by_order(k) --> returns iterator to the kth largest element counting from 0
        order_of_key(val) --> returns the number of items in a set that are strictly smaller than our item
*/
template <typename DT> 
using ordered_set = tree <DT, null_type, less<DT>, rb_tree_tag,tree_order_statistics_node_update>;

const int N = 1000006;
namespace pst {
    //this implementation requires commutativity
    LL sum[22 * N];
    int lft[22 * N], ryt[22 * N], L, R;
    int ptr = 1;
    void build(int tl, int tr, int u = 1) {
        if(tl == tr) return;
        lft[u] = ++ptr, ryt[u] = ++ptr;
        int mid = tl + tr >> 1;
        build(tl, mid, lft[u]);
        build(mid + 1, tr, ryt[u]);
    }
    int update(int u, int idx, LL x, int tl = L, int tr = R) {
        int v = ++ptr;
        lft[v] = lft[u], ryt[v] = ryt[u];
        if(tl == tr) {
            sum[v] = sum[u] + x;
            return v;
        }
        int mid = tl + tr >> 1;
        if(idx <= mid) lft[v] = update(lft[u], idx, x, tl, mid);
        else ryt[v] = update(ryt[u], idx, x, mid + 1, tr);
        sum[v] = sum[lft[v]] + sum[ryt[v]];
        return v;
    }
    LL query(int u, int l, int r, int tl = L, int tr = R) {
        if(l > tr or tl > r) return 0;
        if(l <= tl and tr <= r) return sum[u];
        int mid = tl + tr >> 1;
        return query(lft[u], l, r, tl, mid) + query(ryt[u], l, r, mid + 1, tr);
    }
    void init(int _L, int _R) {
        L = _L, R = _R;
        build(L, R);
    }
};
LL a[N], freq[N];
int up[N];
int query(int tl, int tr, int k, int ul, int ur, int add = 0) {
    if(tl == tr) return tl;
    int mid =  tl + tr >> 1;
    int cnt = pst :: sum[pst :: lft[ur]]- pst :: sum[pst :: lft[ul]];
    if(cnt + add > k) return query(tl, mid, k, pst::lft[ul], pst::lft[ur], add);
    else return query(mid + 1, tr, k, pst::ryt[ul], pst::ryt[ur], add + cnt);
}
/*....................................................................*/ 
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++) cin >> a[i];
    ordered_set <LL> s;
    for(int i = 0; i < n; i++) s.insert(a[i]);
    for(int i = 0; i < n; i++) a[i] = s.order_of_key(a[i] + 1);
    pst :: init(0, n);
    up[0] = 1;
    for(int i = 1; i <= n; i++) {
        up[i] = pst :: update(up[i - 1], a[i - 1], 1);
    }
    while(q--) {
        int l, r, k;
        cin >> l >> r >> k;
        int x = query(0, n, k, up[l], up[r]);
        cout << *s.find_by_order(x - 1) << '\n';
    }
}
