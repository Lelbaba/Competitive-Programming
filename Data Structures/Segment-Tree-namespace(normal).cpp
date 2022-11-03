#include <bits/stdc++.h>
using namespace std;

namespace segtree {
    const int N = 1000006;

    using DT = LL;
    using LT = LL;
    constexpr DT I = 0; 
    constexpr LT None = 0;
    DT val[4 * N];
    LT lazy[4 * N];
    int L, R;

    void pull(int s, int e, int node) {
        val[node] = val[node << 1] + val[node << 1 | 1];
    }
    void apply(const LT &U, int s, int e, int node) {
        val[node] += (e - s + 1) * U;
        lazy[node] += U;
    }
    void reset(int node) {
        lazy[node] = None;
    }
    DT merge(const DT &a, const DT &b) {
        return a + b;
    }
    DT get(int s, int e, int node) {
        return val[node];
    }
    void init(int _L, int _R) {
        L = _L, R = _R;
    }
    void push(int s, int e, int node) {
        if(s == e) return;
        apply(lazy[node], s, s + e >> 1, node << 1);
        apply(lazy[node], s + e + 2 >> 1, e, node << 1 | 1);
        reset(node);
    }
    void build(int s, int e, vector <DT> &v, int node = 1 ) {
        int m = s + e >> 1;
        if(s == e) {
            // do something
        }
        build(s, m, v, node * 2);
        build(m + 1, e, v, node * 2 + 1);
        pull(s, e, node);
    }
    void update(int S,int E, LT uval, int s = L, int e = R, int node = 1) {
        if(S > E) return;
        if(S == s and E == e) {
            apply(uval, s, e, node);
            return;
        }
        push(s, e, node);
        int m = s + e >> 1;
        update(S, min(m, E), uval,  s,  m, node * 2);
        update(max(S, m + 1), E, uval, m + 1, e, node * 2 + 1);
        pull(s, e, node);
    }
    DT query(int S, int E, int s = L, int e = R, int node = 1) {
        if(S > E) return I;
        if(s == S and e == E) return get(s, e, node);
        push(s, e, node);
        int m = s + e >> 1;
        DT L = query(S, min(m, E), s, m, node * 2);
        DT R = query(max(S, m + 1), E, m + 1, e, node * 2 + 1);
        return merge(L, R);
    }
};
int main() {
    return 0;
}