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

    void propagate(int s, int e, int node) {
        if(s == e)
            return;
        tree[node * 2].apply(tree[node].lazy, s, s + e >> 1);
        tree[node * 2 + 1].apply(tree[node].lazy, s + e + 2 >> 1, e);
        tree[node].reset();
    }
    
    void build(vector <DT> &v)      { build(L, R, v);           }
    void update(int S, int E, LT U) { update(S, E, U, L, R);    }
    DT query(int S, int E)          { return query(S, E, L, R); }

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
        if(s == S and e == E) return tree[node].ans(s, e);
        propagate(s, e, node);
        int m = s + e >> 1;
        DT L = query(S, min(m, E), s, m, node * 2);
        DT R = query(max(S, m + 1), E, m + 1, e, node * 2 + 1);
        return tree[node].get(L, R, s, e);
    }
};

pair <LL, LL> compose(const pair <LL, LL> &a, const pair <LL, LL> &b) {
    return make_pair(a.first * b.first % mod, (b.first * a.second % mod + b.second) % mod );
}

void print(const pair <LL, LL> &p) {
    cout << '(' << p.first << ", " << p.second << ") ";
}
struct function_comp {
        using DT = pair <LL, LL>;
        using LT = pair <LL, LL>;
        DT val;
        LT lazy;
        static constexpr DT I = {1, 0}; 
        static constexpr LT None = {0, 0}; 
    
    function_comp(DT val = I, LT lazy = None): val(val), lazy(lazy) {}
    // update functions
    inline void apply(const LT &U, int s, int e) {
        if(U.first == 0) return;
        val = U;
    }
    inline void reset() {
    }
    inline void merge(const function_comp &a, const function_comp &b, int s, int e) {
        val = compose(a.val, b.val);
    }
    // query functions
    inline DT get(const DT &a, const DT &b, int s, int e) {
        return compose(a, b);
    }
    inline DT ans(int s, int e) {
        return val;
    }
};
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector <pair <LL, LL>> a(n);

    segment_tree<function_comp> T(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        T.update(i, i, a[i]);
    }
     
    T.query(0, 0);
    while(q--) {
        int tp;
        cin >> tp;
         
        if(tp) {
            int l, r;
            LL x;
            cin >> l >> r >> x;
            auto [a, b] = T.query(l, r - 1);
            cout << (a * x % mod + b) % mod << '\n';
        } 
        else {
            int p;
            LL c, d;
            cin >> p >> c >> d;
            T.update(p, p, make_pair(c, d));
        }
    }
}
