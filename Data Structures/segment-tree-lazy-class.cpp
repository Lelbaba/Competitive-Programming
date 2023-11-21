#include <bits/stdc++.h>
using namespace std;

using LL = long long;

/*....................................................................*/ 


template <typename VT>
struct segtree {
    using DT = typename VT::DT;
    using LT = typename VT::LT;

    int L, R, counter = 1;
    vector <VT> tr;
    segtree(int n): L(0), R(n - 1), tr(n << 2) {}
    segtree(int l, int r): L(l), R(r), tr((r - l + 1) << 2) {}

    void propagate(int l, int r, int u) {
        if(l == r) return;
        VT :: apply(tr[u << 1], tr[u].lz, l, (l + r) >> 1);
        VT :: apply(tr[u << 1 | 1], tr[u].lz, (l + r + 2) >> 1, r);
        tr[u].lz = VT :: None;
    }

    void build(int l, int r, vector <DT> &v, int u = 1 ) {
        if(l == r) {
            tr[u].val = v[l];
            return;
        }
        int m = (l + r) >> 1, lft = u << 1, ryt = u << 1 | 1;
        build(l, m, v, lft);
        build(m + 1, r, v, ryt);
        tr[u].val = VT :: get(tr[lft].val, tr[ryt].val, l, r);
    }

    void update(int ql,int qr, LT up, int l, int r, int u = 1) {
        if(ql > qr) return;
        if(ql == l and qr == r) {
            VT :: apply(tr[u], up, l, r);
            return;
        }
        propagate(l, r, u);
        int m = (l + r) >> 1, lft = u << 1, ryt = u << 1 | 1;
        update(ql, min(m, qr), up,  l,  m, lft);
        update(max(ql, m + 1), qr, up, m + 1, r, ryt);
        tr[u].val = VT :: get(tr[lft].val, tr[ryt].val, l, r);
    }

    DT query(int ql, int qr, int l, int r, int u = 1) {
        if(ql > qr) return VT::I;
        if(l == ql and r == qr)
            return tr[u].val;
        propagate(l, r, u);
        int m = (l + r) >> 1, lft = u << 1, ryt = u << 1 | 1;
        DT ansl = query(ql, min(m, qr), l, m, lft);
        DT ansr = query(max(ql, m + 1), qr, m + 1, r, ryt);
        return tr[u].get(ansl, ansr, l, r);
    }

    void build(vector <DT> &v) { build(L, R, v); }
    void update(int ql, int qr, LT U) { update(ql, qr, U, L, R); }
    DT query(int ql, int qr) { return query(ql, qr, L, R); }
};


struct add_sum {
    using DT = LL;
    using LT = LL;
    DT val;
    LT lz;

    static constexpr DT I = 0; 
    static constexpr LT None = 0;
    
    add_sum(DT _val = I, LT _lz = None): val(_val), lz(_lz) {}

    static void apply(add_sum &u, const LT &up, int l, int r) {
        u.val += (r - l + 1) * up;
        u.lz += up;
    }

    static DT get(const DT &a, const DT &b, int l, int r) {
        return a + b;
    }
};

/*....................................................................*/ 

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int T;
    cin >> T;

    for(int tc = 1; tc <= T; tc++) {
        int n, m;
        cin >> n >> m;
        segtree <add_sum> Tree(n);
        segtree <affine> Tree2(n);
        cout << "Case " << tc << ":\n"; 
        while(m--) {
            int tp, l, r;
            cin >> tp >> l >> r;
            if(tp) {
                cout << Tree.query(l, r) << '\n';
            } else {
                LL up;
                cin >> up;
                Tree.update(l, r, up);
            }
        }
    }
}