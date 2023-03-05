#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const LL mod = 998244353;

template <typename VT>
struct segment_tree {
    using DT = typename VT::DT;
    using LT = typename VT::LT;
        int L, R, counter = 1;
        vector <VT> tree;
    segment_tree(int n): L(0), R(n-1), tree(n<<2) {}
    segment_tree(int s, int e): L(s), R(e), tree(e-s+1 << 2) {}

    void build(vector <DT> &v)      { build(L, R, v);           }
    void update(int S, int E, LT U) { update(S, E, U, L, R);    }
    DT query(int S, int E)          { return query(S, E, L, R); }

    void propagate(int s, int e, int node) {
        if(s == e)
            return;
        tree[node * 2].apply(tree[node].lazy, s, s + e >> 1);
        tree[node * 2 + 1].apply(tree[node].lazy, s + e + 2 >> 1, e);
        tree[node].reset();
    }
    
    
    void build(int s, int e, vector <DT> &v, int node = 1 ) {
        int m = s + e >> 1;
        if(s == e) {
            tree[node] = VT(v[s]);
            return;
        }
        build(s, m, v, node * 2);
        build(m + 1, e, v, node * 2 + 1);
        tree[node].merge(tree[node * 2], tree[node * 2 + 1], s, e);
    }

    void update(int S,int E, LT uval, int s, int e, int node = 1) {
        if(S > E) return;
        if(S == s and E == e) {
            tree[node].apply(uval, s, e);
            return;
        }
        propagate(s, e, node);
        int m = s + e >> 1;
        update(S, min(m, E), uval,  s,  m, node * 2);
        update(max(S, m + 1), E, uval, m + 1, e, node * 2 + 1);
        tree[node].merge(tree[node*2], tree[node*2+1], s, e);
    }

    DT query(int S, int E, int s, int e, int node = 1) {
        if(S > E) return VT::I;
        if(s == S and e == E)
            return tree[node].ans(s, e);
        propagate(s, e, node);
        int m = s + e >> 1;
        DT L = query(S, min(m, E), s, m, node * 2);
        DT R = query(max(S, m + 1), E, m + 1, e, node * 2 + 1);
        return tree[node].get(L, R, s, e);
    }
};
pair <LL, LL> compose(const pair <LL, LL> &a, const pair <LL, LL> &b){
    return make_pair(a.first * b.first % mod, (b.first * a.second % mod + b.second) % mod);
}
struct affine {
        using DT = LL;
        using LT = pair <LL, LL>;
        DT val;
        LT lazy;
        static constexpr DT I = 0; 
        static constexpr LT None = {1, 0};
    
    affine(DT val = I, LT lazy = None): val(val), lazy(lazy) {}
    // update functions
    inline void apply(const LT &U, int s, int e) {
        (val *= U.first) %= mod;
        (val += (e - s + 1) * U.second % mod) %= mod;
        lazy = compose(lazy, U);
    }
    inline void reset() {
        lazy = None;
    }
    inline void merge(const affine &a, const affine &b, int s, int e) {
        val = (a.val + b.val) % mod;
    }
    // query functions
    inline DT get(const DT &a, const DT &b, int s, int e) {
        return (a + b) % mod;
    }
    inline DT ans(int s, int e) {
        return val;
    }
};
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector <LL> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    segment_tree <affine> T(n);
    T.build(a);
    while(q--) {
        int tp;
        cin >> tp;
        if(tp) {
            int l, r;
            cin >> l >> r;
            cout << T.query(l, r - 1) << '\n';
        } else {
            int l, r;
            LL b, c;
            cin >> l >> r >> b >> c;
            T.update(l, r - 1, make_pair(b, c));
        }
    }
}
