#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using ll = long long;
const int MONKE = 0;
template <typename DT>
class vertex{
    public:
        DT val, lazy, iden = 0;
        int l, r, state = -1;
    vertex(DT _val = 0, DT _lazy = 0){
        // default values should be the identity 
        val = _val, lazy = _lazy;
    }
    DT add(DT a,DT b){
        return a+b;
    }
    DT repeat(DT a){
        return a*(r-l+1);
    }
    void base_state(DT x){
        val = x;
        state = 0;
    }
    void base_update(DT x){
        lazy = add(lazy,x);
        val = add(val,repeat(x));
    }
    void merge(vertex L,vertex R){
        if(state == -1)
            state = 0;
        val = add(add(L.val,R.val),repeat(lazy));
    }
    void propogate(vertex& L,vertex& R){
        L.base_update(lazy);
        R.base_update(lazy);
        lazy = iden;
    }
    DT ans(){
        return val;
    }
};

template <typename VT, typename DT>
class lazy_segment_tree
{
    public:
        int n;
        vector <VT> tree;
        vector <DT> arr;
        VT tem;

    lazy_segment_tree(vector <DT> &v){
        n = v.size();
        arr = v;
        tree.resize(n*4);
        build();
    }
    void build(){
        build(0,n-1);
    }
    void build(int l,int r,int node = 1){
        tree[node].l = l, tree[node].r = r;
        if(l==r){
            tree[node].base_state(arr[l]);
        } else{
            int m = l+(r-l)/2;
            build(l,m,node*2);
            build(m+1,r,node*2+1);
            tree[node].merge(tree[node*2],tree[node*2+1]);
        }
    }

    void update(DT uval,int ul,int ur, int node = 1){
        int l = tree[node].l, r = tree[node].r;

        if(ul>ur){
            return;
        }
        if(l==ul and r==ur){
            tree[node].base_update(uval); 
        } else {
            int m = (r+l)/2, _ul = max(ul,m+1), _ur = min(ur,m);

            update(uval,ul, _ur,node*2);
            update(uval,_ul,ur, node*2+1);

            tree[node].merge(tree[node*2],tree[node*2+1]);
        }
    }

    DT query(int ql,int qr,int node  = 1){
        int l = tree[node].l, r = tree[node].r;

        if(ql>qr){
            return tem.iden;
        }
        if(l==ql && r==qr){
            return tree[node].ans();
        }

        tree[node].propogate(tree[node*2],tree[node*2+1]);

        int m = l + (r-l)/2, _ql = max(ql,m+1), _qr = min(qr,m);
        return tem.add(query(ql, _qr, node*2),
                   query(_ql,qr, node*2+1));
    }  
};

int main()
{
    monke_flip
    int T;
    cin>>T;
    for(int tc=1;tc<=T;tc++){
        int n,q;
        cin>>n>>q;
        cout<<"Case "<<tc<<":\n";
        vector <ll> v(n);
        lazy_segment_tree<vertex<ll>, ll> T(v);
        for(int i=0;i<q;i++){
            int type,l,r;
            ll val;
            cin>>type;
            if(type == 0){
                cin>>l>>r>>val;
                T.update(val,l,r);
            } else{
                cin>>l>>r;
                ll ans = T.query(l,r);
                cout<<ans<<'\n';
            }
        }
    }
    return MONKE;
}