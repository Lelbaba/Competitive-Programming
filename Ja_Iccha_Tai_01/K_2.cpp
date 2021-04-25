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

class DSU
{
    public:
        vector <int> par,size;
        // parent of each set and size of each set
    DSU(int n){
        for(int i=0;i<n;i++){
            par.push_back(i);
            size.push_back(1);
        }
    }
    // ancestor
    int Anc(int node){
        if(par[node] == node) 
            return node;
        return par[node] = Anc(par[node]); 
    }
    bool same(int x,int y){
        return Anc(x) == Anc(y);
    }
    void Union(int x,int y){
        x = Anc(x),y = Anc(y);
        size[x] += size[y];
        par[y] = x;
    }
};
int main()
{
    monke_flip
    int n;
    cin>>n;
    vector <int> v(n),id(n),ans(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
        id[i] = i;
    }
    auto comp = [&](int a,int b){
        return v[a]>v[b] or (v[a]==v[b] and a>b);
    };
    sort(id.begin(),id.end(),comp);
    DSU D(n);
    for(int i=0,j=0;i<n;i++){
        if(id[i]>0 and comp(id[i]-1,id[i])) D.Union(id[i],id[i]-1);
        if(id[i]<n-1 and comp(id[i]+1,id[i])) D.Union(id[i],id[i]+1);
        for(;j<D.size[id[i]];j++)
            ans[j] = v[id[i]];
    }
    for(auto x:ans) cout<<x<<" ";
    return MONKE;
}