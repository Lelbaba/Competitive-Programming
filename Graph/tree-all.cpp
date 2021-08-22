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

class Tree{
    public:
        int n, time = 0, LOG = 25;
        vector <vector <int> > adj;
        vector <vector <int>> anc;
        vector <int> start, finish, level, par;

    Tree(int n = 0) : n(n), adj(vector <vector <int>>(n)){}
    Tree(vector <pair <int,int>> edges): n(1 + edges.size()) {
        adj.resize(n);
        for(auto &[u,v]: edges){
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    void call(int node, int p = -1){
        if(p != -1)
            level[node] = level[p] + 1;
        start[node] = time++;
        for(int e: adj[node]){
            if(e == p)
                continue;
            call(e, node);
        }
        par[node] = p; 
        finish[node] = time++;
    }
    void init(int root){
        start.resize(n), finish.resize(n), level.resize(n), par.resize(n);
        time = 0;
        call(root);
    }
    int subtree_size(int node){
        return finish[node] - start[node] + 1 >> 1;
    }
    bool is_ancestor(int node, int par){
        return start[par] <= start[node] and finish[par] >= finish[node];
    }
    void setup_lifting(int node, int par) {
        for (int v: adj[node]) {
            if(v == par)
                continue;
            anc[v][0] = node;
            level[v] = level[node] + 1;
            for (int k=1; k<LOG; k++)     
                anc[v][k] = anc[anc[v][k-1]][k-1];
            setup_lifting(v, node);
        }
    }
    void init_lifting(int root){
        LOG = 33 - __builtin_clz(n);
        anc.assign(n, vector <int> (LOG, root));
        level.resize(n);
        setup_lifting(root, root);
    }
    int lca(int u, int v) {
        if (level[u] > level[v])
            swap(u, v);
        for (int k = LOG-1; k>=0; k--)
            if (level[u] + (1<<k) <= level[v])
                v = anc[v][k];
        if (u == v) 
            return u;
        for (int k=LOG-1; k>=0; k--)
            if (anc[u][k] != anc[v][k])
                u = anc[u][k], v = anc[v][k];
        return anc[u][0];
    }
    int getanc(int node, int ht) {
        for (int k=0; k<LOG; k++)
            if (ht & (1<<k))
                node = anc[node][k];
        return node;
    }
    int dis(int u, int v) {
        int g = lca(u, v);
        return level[u] + level[v] - 2*level[g];
    }
};
int main()
{
    monke_flip
    return MONKE;
}