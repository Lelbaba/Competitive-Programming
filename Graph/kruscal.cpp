#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke chrono::system_clock::now().time_since_epoch().count()
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using LL = long long;
using ULL = unsigned long long;
mt19937_64 rng(random_monke);
const int MONKE = 0;

/*....................................................................*/ 
class DSU{
    vector <int> par,size;
    public:
    DSU(int n): par(n), size(n, 1) {
        iota(par.begin(), par.end(), 0);
    }
    int Anc(int node){
        return par[node] = (par[node] == node) ? node : Anc(par[node]); 
    }
    inline bool same(int x, int y){
        return Anc(x) == Anc(y);
    }
    inline void Union(int x, int y){
        x = Anc(x), y = Anc(y), size[x] += size[y], par[y] = x;
    }
    inline int Size(int node){
        return size[Anc(node)];
    }
};
template <typename WT> using edge = tuple <WT, int, int>; // weight should be first
template <typename WT> vector < edge<WT> > Kruscal(int n, vector <edge <WT>> &edges){
    DSU tree(n);
    sort(edges.begin(), edges.end());
    vector <edge <WT>> ans;
    for(auto &[w, l, r] : edges) {
        if( !tree.same(l,r) ){
            ans.emplace_back(w, l, r);
            tree.Union(l, r);
        }
    }
    return ans;
}
/*....................................................................*/ 

void solve(){
    int n, m;
    cin >> n >> m;
    if(n == 0 and m == 0)
        exit(0);
    LL ans = 0;
    vector < edge <int>> edges(m);
    for (auto &[w, l, r] : edges) {
        cin >> l >> r >> w;
        ans += w;
    }
    auto MSP = Kruscal(n, edges);
    for(auto &[w, l, r] : MSP)
        ans -= w;
    cout << ans << '\n';

}

int main()
{
    monke_flip
    while(!MONKE)
        solve();
}