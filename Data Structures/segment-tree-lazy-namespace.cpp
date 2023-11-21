#include <bits/stdc++.h>
using namespace std;
using LL = long long;

/*--------------------------------------------------
 * There are six things you need to worry about

    * The data type of the values on the nodes: DT
    * The data type of the updates on the nodes: LT
        Lazy data will be the same as an update
        Lazy data is the update that has ALREADY BEEN 
        PROCESSED on this node, and WILL BE PUSHED down
        to the childred later, value is always updated.
    * How does the value and lazy data of a node change
        when a new update comes : apply()
        Merging of updates take place here
    * How to merge the results of two nodes while answering
        queries : merge()
    * What is the identity of apply() : None
        This is equivalent to "No update", should represent an
        update which changes nothing
    * What is the identity of merge() : I
        This is the equivalent to answering queries in an empty
        range, a value that will never change the result of an
        answer

 *--------------------------------------------------*/

namespace segtree {
    const int N = 1000006;

    using DT = LL;
    using LT = LL;
    constexpr DT I = 0; 
    constexpr LT None = 0;

    DT val[4 * N];
    LT lz[4 * N];
    int L, R;

    void apply(int u, const LT &U, int l, int r) {
        val[u] += (r - l + 1) * U;
        lz[u] += U;
    }

    DT merge(const DT &a, const DT &b, int l, int r) {
        return a + b;
    }
    /* -- Do Not Touch Anything Below This -- */

    void push(int l, int r, int u) {
        if(l == r) return;
        apply(u << 1, lz[u], l, (l + r) >> 1);
        apply(u << 1 | 1, lz[u], (l + r + 2) >> 1, r);
        lz[u] = None;
    }

    void build(int l, int r, vector <DT> &v, int u = 1 ) {
        lz[u] = None;
        if(l == r) {
            val[u] = v[l];
            return;
        }
        int m = (l + r) >> 1, lft = u << 1, ryt = lft | 1;
        build(l, m, v, lft);
        build(m + 1, r, v, ryt);
        val[u] = merge(val[lft], val[ryt], l, r);
    }
    void update(int ql,int qr, LT uval, int l = L, int r = R, int u = 1) {
        if(ql > qr) return;
        if(ql == l and qr == r) {
            apply(u, uval, l, r);
            return;
        }
        push(l, r, u);
        int m = (l + r) >> 1, lft = u << 1, ryt = lft | 1;
        update(ql, min(m, qr), uval,  l,  m, lft);
        update(max(ql, m + 1), qr, uval, m + 1, r, ryt);
        val[u] = merge(val[lft], val[ryt], l, r);
    }
    DT query(int ql, int qr, int l = L, int r = R, int u = 1) {
        if(ql > qr) return I;
        if(l == ql and r == qr) return val[u];
        push(l, r, u);
        int m = (l + r) >> 1, lft = u << 1, ryt = lft | 1;
        DT ansl = query(ql, min(m, qr), l, m, lft);
        DT ansr = query(max(ql, m + 1), qr, m + 1, r, ryt);
        return merge(ansl, ansr, l, r);
    }
    void init(int _L, int _R, vector <DT> &v) {
        L = _L, R = _R;
        build(L, R, v);
    }
};
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int T;
    cin >> T;

    for(int tc = 1; tc <= T; tc++) {
        int n, m;
        cin >> n >> m;
        vector <LL> a(n);
        segtree :: init(0, n - 1, a);
        cout << "Case " << tc << ":\n"; 
        while(m--) {
            int tp, l, r;
            cin >> tp >> l >> r;
            if(tp) {
                cout << segtree :: query(l, r) << '\n';
            } else {
                LL up;
                cin >> up;
                segtree :: update(l, r, up);
            }
        }
    }
}
