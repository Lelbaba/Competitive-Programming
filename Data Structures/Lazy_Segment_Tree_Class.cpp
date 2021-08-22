#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using LL = long long;
const int MONKE = 0;
/*
        segment tree class merely handles segment tree operations
        and the attempt here is to employ it in such a way that
        there would be no need to change that part of the code

        vertex class needs to handle everything that a segment tree 
        needs.
        VT, DT, LT are the vertex class, query return type, and update type
        respectively

        requirements from the vertex class:
        a constructor that takes the query return type as an argument
        a lazy value that contains update types
        member functions:
        apply:
            given an update type and range of the node, it will apply the update 
            to a node
        reset:
            will clear all pending operations in lazy
        merge:
            given child nodes, will combine them to form the current node
        get:
            given two results of queries from child node and current range
            will give the result for this node
        ans:
            in the case of a leaf, will give the result

        ostream must be defined to use check

*/

class range_sum{
    // horrible queries
    public:
        LL val = 0, lazy;
        const static LL I = 0;
    range_sum() = default;
    range_sum(LL v) : val(v), lazy(0) {}
    void apply(LL up, int s, int e){
        val += up * (e-s+1);
        lazy += up;
    }
    void reset(){
        lazy = 0;
    }
    void merge(range_sum &a, range_sum &b){
        val = a.val + b.val;
    }
    LL get(LL a, LL b, int s, int e){
        return a + b;
    }
    LL ans(int s){
        return val;
    }
    friend ostream& operator << (ostream& o, range_sum &a){
        o << "val = "<< a.val << "\nlazy = " << a.lazy << '\n';
        return o;
    }
};

rho

class range_frequency{
    //CF 1555 E
    public:
        LL val = 0, lazy, cnt = 0;
        const static LL I = 1;
    range_frequency() = default;
    range_frequency(LL v) : val(v), lazy(0) {}
    void apply(LL up, int s, int e){
        lazy += up;
        cnt += up;
        val = cnt > 0;
    }
    void reset(){
        lazy = 0;
    }
    void merge(range_frequency &a, range_frequency &b, int s, int e){
        cnt = min(a.cnt,b.cnt);
        val = a.val & b.val;
    }
    LL get(LL a, LL b, int s, int e){
        return a & b;
    }
    LL ans(int s){
        return val;
    }
    friend ostream& operator << (ostream& o, range_frequency &a){
        o << "val = "<< a.val << "\nlazy = " << a.lazy << '\n';
        return o;
    }
};

class pirate_counter{
    // AHOY PIRATES
    const static char one = 'F', zero = 'E', invert = 'I', query = 'S';
    public:
        static const int I = 0; 
        int val = I;
        char lazy;
    pirate_counter() = default;
    pirate_counter(int val, char lazy = 0) : val(val), lazy(lazy){} //lazy should be applicable like an update

    void apply(char c, int s, int e){ 
        if(c == one){
            val = e - s + 1;
            lazy = one;
        } else if(c == zero){
            val = 0;
            lazy = zero;
        } else if(c == invert){
            val = e - s + 1 - val;
            if(lazy == one)
                lazy = zero;
            else if(lazy == zero)
                lazy = one;
            else if(lazy == invert)
                lazy = 0;
            else 
                lazy = invert;
        }
    }
    void reset(){
        lazy = 0;
    }
    void merge(pirate_counter &A, pirate_counter &B, int s, int e){
        val = A.val + B.val;
    }
    int get(int a, int b, int s = 0,int e = 0){
        return a+b;
    }
    int ans(int s){
        return val;
    }
    friend ostream& operator << (ostream &os, const pirate_counter& v){
        os << "val = " << v.val << '\n';
        os << "lazy = " << v.lazy << '\n';
        return os;
    } 
};


template <typename VT, typename DT, typename LT>
class segment_tree{
    public:
        int L, R, counter = 1;
        vector <VT> tree;
    segment_tree(int n): L(0), R(n-1), tree(n<<2) {}
    segment_tree(int s, int e): L(s), R(e), tree(e-s+1 << 2) {}
    void propogate(int s, int e, int node){
        if(s == e)
            return;
        tree[node*2].apply(tree[node].lazy, s, s+e>>1);
        tree[node*2+1].apply(tree[node].lazy, s+e+2>>1, e);
        tree[node].reset();
    }
    
    void build(vector <DT> &v)      { build(L, R, v);           }
    void update(int S, int E, LT U) { update(S, E, U, L, R);    }
    DT query(int S, int E)          { return query(S, E, L, R); }
    void check()                    { return check(L, R);       }

    void build(int s, int e, vector <DT> &v, int node = 1 ){
        int m = s + e >> 1;
        if(s == e){
            tree[node] = VT(v[s]);
            return;
        }
        build(s, m, v, node * 2);
        build(m+1, e, v, node*2+1);
        tree[node].merge(tree[node*2], tree[node*2+1], s, e);
    }
    void update(int S,int E, LT uval, int s, int e, int node = 1){
        propogate(s, e, node);
        int m = s + e >> 1;
        if(S>E)
            return;
        if(S == s and E == e){
            tree[node].apply(uval, s, e);
            return;
        }
        update(S,   min(m,E), uval,  s,  m, node * 2);
        update(max(S,m+1), E, uval, m+1, e, node * 2 + 1);
        tree[node].merge(tree[node*2], tree[node*2+1], s, e);
    }
    DT query(int S, int E, int s, int e, int node = 1){
        propogate(s, e, node);
        int m = s + e >> 1;
        if(S>E)
            return VT::I;
        if(s == S and e == E)
            return tree[node].ans(s);
        DT L = query(S, min(m,E), s, m, node*2);
        DT R = query(max(S,m+1), E, m+1, e, node*2+1);
        return tree[node].get(L, R, s, e);
    }
    void chk(int s, int e, int node = 1){
        int m = s+e >> 1;
        cerr << ".........................\n";
        cerr << "RANGE : " << s <<" - "<< e <<'\n';
        cerr << tree[node] << '\n';
        if(s == e) 
            return ;
        chk(s,m,node*2);
        chk(m+1,e,node*2+1);

    }
    void check(int s, int e){
        cerr << "\n\n";
        cerr <<"........ Commencing Check : "<< counter++ << " ........\n";
        chk(s, e);
    }
};

void solve(){
    string pirates, tem;
    int M, T;
    cin >> M;
    for(int i = 0; i< M; i++){
        cin >> T >> tem;
        for(int j = 0; j < T; j++)
            pirates += tem;
    }
    int n = pirates.size();
    segment_tree < pirate_counter ,int, char> Tree(n);
    vector <int> prt(n);
    for(int i = 0; i < n; i++)
        prt[i] = pirates[i] - '0';

    Tree.build(0,n-1,prt);
    cin >> T;
    Tree.check(0,n-1);
    for(int i = 0, l, r, q = 1; i< T; i++){
        char ch;
        cin >> ch >> l >> r;
        if(ch == 'S'){
            cout <<'Q'<<q++<<": " <<Tree.query(l,r,0,n-1)<<'\n';
            Tree.check(0, n-1);
        } else {
            Tree.update(l,r,ch, 0, n-1);
            Tree.check(0,n-1);
        }
    }
}
int main()
{
    monke_flip
    int t = 1; 
    cin>>t;
    for(int tc=1; tc<=t; tc++){
        cout << "Case "<<tc<<":\n";
        solve();
    }
    return MONKE;
}