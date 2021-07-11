#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif
//CF 1540 B
using namespace std;
using ll = long long;
const int MONKE = 0, N = 201, K = 11;

ll bigmod(ll num,ll pow,ll mod){
    num = num%mod;
    ll ans = 1;
    for(;pow>0;pow>>=1){
        if(pow&1) ans = ans*num % mod;
        num = num*num % mod;
    }
    return ans;
}
// one-indexed
class tree{

public:
    int N, K;
    vector <vector <int>> adj, anc;
    vector <int> level;

    tree(vector <pair<int,int>> &edges){
        N = edges.size() + 1;
        K = 33 - __builtin_clz(N);
        
        adj.assign(N+1, vector<int>());
        level.assign(N+1,0);
        anc.assign(N+1, vector <int>(K));

        for(auto &[u,v]: edges){
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    void setup(int node, int par = 0) {
        level[node] = level[par]+1;
        anc[node][0] = par;

        for (int k=1; k<K; k++)     
            anc[node][k] = anc[anc[node][k-1]][k-1];
        for (int v: adj[node]) {
            if (v == par)   continue;
            setup(v, node);
        }
    }
    int lca(int u, int v) {
        if (level[u] > level[v])
            swap(u, v);
        for (int k = K-1; k>=0; k--)
            if (level[u] + (1<<k) <= level[v])
                v = anc[v][k];
        if (u == v) 
            return u;
        for (int k=K-1; k>=0; k--)
            if (anc[u][k] != anc[v][k])
                u = anc[u][k], v = anc[v][k];
        return anc[u][0];
    }
    int getanc(int node, int ht) {
        for (int k=0; k<K; k++)
            if (ht & (1<<k))
                node = anc[node][k];
        return node;
    }
    int dis(int u, int v) {
        int g = lca(u, v);
        return level[u] + level[v] - 2*level[g];
    }
};

ll P[205][205];
const ll mod = 1e9+7;
void calc(){
    for(int i=1;i<201; i++){
        P[i][0] = 0;
        P[0][i] = 1;
    }
    ll half = bigmod(2,mod-2,mod);
    for(int i=1; i<201; i++){
        for(int j=1; j<201; j++){
            P[i][j] = (P[i][j-1] + P[i-1][j]) * half % mod; 
        }
    }
}

int main()
{
    monke_flip
    int n;
    cin>>n;
    vector <pair <int,int>> edges(n-1);
    for(auto &[u,v]:edges){
        cin >> u >> v;
    }
    calc();
    ll ans = 0;
    tree gach(edges);
    for(int root=1; root<=n;root++){
        gach.setup(root);
        for(int u=1; u<=n; u++){
            for(int v=1; v<u; v++){
                int L = gach.lca(u,v);
                ans = (ans + P[gach.dis(u,L)][gach.dis(v,L)])%mod; 
            }
        }
    }
    ans = (ans * bigmod(n, mod-2, mod))%mod;
    cout<<ans;
    return MONKE;
}