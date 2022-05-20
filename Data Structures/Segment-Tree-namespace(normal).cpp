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
const int one = 'F', zero = 'E', invert = 'I', query = 'S'; 

namespace Tree{
    class vertex{
        public:
        int val, lazy;
        vertex(int _val = 0, int _lazy = 0){
            val = _val, lazy = _lazy;
        }
    };
    array <vertex, (1<<22) + 10> T;
    void build(int S,int E, string &str, int node = 1){
        int m = S+E >> 1, &val = T[node].val, &lazy = T[node].lazy;
        lazy  = 0;
        if(S == E){
            val = (str[S] == '1');
        } else {
            build(S, m, str, node*2);
            build(m+1,E, str, node*2+1);
            val = T[node*2].val + T[node*2+1].val;
        }
    }

    void apply(int c, int node, int s, int e){
        int &val = T[node].val, &lazy = T[node].lazy;
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
    void propogate(int node, int s, int e){
        if(s == e)
            return;
        int m = s+e>>1;
        int &lazy = T[node].lazy;
        apply(lazy, node*2,s,m);
        apply(lazy, node*2+1,m+1,e);
        lazy  = 0;
    }
    void check(int s, int e, int node = 1){
        int m = s+e >> 1;
        cerr << ".........................\n";
        cerr << "RANGE : " << s <<' '<< e <<'\n';
        cerr << "val = " << T[node].val << '\n';
        cerr << "lazy = " << (char) T[node].lazy << '\n' <<'\n';
        if(s == e) 
            return ;
        check(s,m,node*2);
        check(m+1,e,node*2+1);

    }
    void update(int L, int R, int uval, int S, int E, int node = 1){
        int m = S+E >> 1, &val = T[node].val, &lazy = T[node].lazy;
        propogate(node, S, E);
        if(L>R)
            return;
        if(L == S and R == E){
            apply(uval, node , S, E);
            return;
        }
        update(L, min(m,R), uval, S, m, node * 2);
        update(max(m+1, L), R, uval, m+1, E, node*2+1);
        val = T[node*2].val + T[node*2+1].val;
    }
    int query(int L,int R, int s, int e, int node = 1){
        propogate(node, s, e);
        int m = s+e >> 1, &val = T[node].val, &lazy = T[node].lazy;
        if(L>R)
            return 0;
        if(L == s and e == R)
            return val;
        return query(L,min(m,R),s,m, node*2)+ query(max(L,m+1), R, m+1, e, node*2+1);
    }
};
namespace Segment_Tree{
    struct Node {
        LL val, lazy;
        Node *left, *right;
        Node(LL val = 0, LL lazy = 0) : val(val), lazy(lazy) {}
    };
    const int N = 1e5 + 5;
    vector <Node> tree;
    Node* NewNode() {
        tree.emplace_back();
        return &tree.back();
    }
    const LL I = 0;
    void apply(Node* node, int s, int e, LL up) {
        node -> val += up * (e - s + 1);
        node -> lazy += up;
    }
    void merge(Node* node, int s, int e) {
        node -> val = node -> left -> val + node -> right -> val;
    }
    void reset(Node* node, int s, int e) {
        node -> lazy = 0;
    }
    LL get(int s, int e, LL a, LL b) {
        return a + b;
    }
    LL ans(Node* node, int s, int e) {
        return node -> val;
    }
    void propagate(Node* node, int s, int e) {
        apply(node -> left, s, s + e >> 1, node -> lazy);
        apply(node -> right, s + e + 2 >> 1, e, node -> lazy);
        reset(node, s, e);
    }
    void build(Node* node, int s, int e, vector <LL> &v) {
        if(s == e){
            node -> val = v[s];
            return;
        }
        node -> left = NewNode();
        node -> right = NewNode();
        int m = s + e >> 1;
        build(node -> left, s, m, v);
        build(node -> right, m + 1, e, v);
        merge(node, s, e);
    }
    void update(Node* node, int s, int e, int _s, int _e, LL up) {
        _s = max(_s, s), _e = min(_e, e);
        if(_s > _e) return;
        if(_s == s and _e == e) {
            apply(node, s, e, up);
            return;
        }
        propagate(node, s, e);
        int m = s + e >> 1;
        update(node -> left, s, m, _s, _e, up);
        update(node -> right, m + 1, e, _s, _e, up);
        merge(node, s, e);
    }
    LL query(Node *node, int s, int e, int _s, int _e) {
        _s = max(_s, s), _e = min(_e, e);
        if(_s > _e) return I;
        if(_s == s and _e == e) return ans(node, s, e);

        propagate(node, s, e);
        int m = s + e >> 1;
        LL L = query(node -> left, s, m, _s, _e);
        LL R = query(node -> right, m + 1, e, _s, _e);
        return get(s, e, L, R);
    }
}
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
    Tree::build(0,n-1,pirates);
    cin >> T;
    for(int i = 0, l, r, q = 1; i< T; i++){
        char ch;
        cin >> ch >> l >> r;
        if(ch == query){
            cout <<'Q'<<q++<<": " <<Tree::query(l,r,0,n-1)<<'\n';
        } else {
            Tree::update(l,r,ch, 0, n-1);
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
