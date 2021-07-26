#include <bits/stdc++.h>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#ifdef LEL
#include "dbg.h"
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using ll = long long;
const int MONKE = 0;

class segment_tree
{
public:
	int n;
    vector <ll> arr,tree,lazy;

    segment_tree(vector <ll> &v){
        n = v.size();; 
        arr = v;
        tree.assign(n*4,0);
        lazy.assign(n*4,0);
        build();
    }
    void build(){
        build(0,n-1);
    }
    void update(ll l,ll r,ll val){
        update(l,r,val,0,n-1);
    }
    ll query(ll l,ll r){
        return query(l,r,0ll,0,n-1);
    }
    void build(ll l,ll r,ll node = 1){
        if(l==r){
            tree[node] = arr[l]; 
        } else{
            ll m = l+(r-l)/2;
            build(l,m,node*2);
            build(m+1,r,node*2+1);
            tree[node] = tree[node*2]+tree[node*2+1];
        }
    }

    void update(ll ul,ll ur,ll uval,ll l,ll r,ll node = 1){
        if(ul>ur){
            return;
        }
        if(l==ul && r==ur){
            lazy[node] += uval;
            tree[node] += uval*(r-l+1);
        } else {
            ll m = l + (r-l)/2, _ul = max(ul,m+1), _ur = min(ur,m);
            update(ul, _ur,uval, l,  m, node*2);
            update(_ul,ur,uval, m+1, r, node*2+1);
            tree[node] = tree[node*2] + tree[node*2+1]+lazy[node]*(r-l+1);
        }
    }

    ll query(ll ql,ll qr,ll prop,ll l,ll r,ll node  = 1){

        if(ql>qr){
            return 0;
        }
        if(l==ql && r==qr){
            return prop*(r-l+1) + tree[node];
        }
        ll m = l + (r-l)/2, _ql = max(ql,m+1), _qr = min(qr,m);
        return query(ql, _qr, prop+lazy[node], l,  m, node*2)
               + query(_ql,qr,prop+lazy[node], m+1, r, node*2+1);
    }  
};
int main()
{
    int t;
    cin>>t;
    for(int tc=1;tc<=t;tc++){
        int n,m;
        printf("Case %d:\n", tc);
        scanf("%d%d", &n,&m);
        vector <ll> v(n);
        segment_tree T(v);

        for(int i=0;i<m;i++){
            int type,l,r;
            ll val;
            scanf("%d", &type);
            if(type == 0){
                scanf("%d%d%lld", &l,&r,&val);
                T.update(l,r,val);
            } else{
                scanf("%d%d", &l,&r);
                ll ans = T.query(l,r);
                printf("%lld\n",ans);
            }
        }
    }
    return MONKE;
}