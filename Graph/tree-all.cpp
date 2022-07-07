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
    int time = 0;
    vector <vector <int> > adj;
    vector <int> start, finish, level, par;
public:
    int n;
    vector <vector <int> > col;
    inline vector<int>& operator[](int u) { 
        return adj[u]; 
    }
    Tree(int n = 0) : n(n), adj(n), col(n) {}
    void AddEdge(int u, int v, int c){
        adj[u].push_back(v);
        adj[v].push_back(u);
        col[u].push_back(c);
        col[v].push_back(c);
    }
};
set <int> GetCenters(Tree &T){
    int n = T.n;
    vector <uint32_t> deg(n), q;
    set <int> s;
    for(int i = 0; i < n; i++){
        deg[i] = T[i].size();
        if(deg[i] == 1)
            q.push_back(i);
        s.insert(i);
    }
    while(s.size() > 2){
        vector <uint32_t> t;
        for(auto x: q) {
            for(auto e: T[x]){
                if(--deg[e] == 1)
                    t.push_back(e);
            }
            s.erase(x);
        }
        q = t;
    }
    return s;
}
struct DFS_Timer {
    int time = 0;
    vector <int> start, finish, level, par;
    int n;
    Tree &T;
    DFS_Timer(Tree &T, int root = 0) : T(T), n(T.n), start(n), finish(n), level(n), par(n) {
        time = 0;
        Call(root);
    }
    void Call(int node, int p = -1){
        if(p != -1) level[node] = level[p] + 1;
        start[node] = time++;
        for(int e: T[node]) if(e != p) 
            Call(e, node);
        par[node] = p; 
        finish[node] = time++;
    }
    bool IsAncestor(int node, int par){
        return start[par] <= start[node] and finish[par] >= finish[node];
    }
    int SubtreeSize(int node){
        return finish[node] - start[node] + 1 >> 1;
    }
};
struct LCA_Table {
    Tree &T;
    int n, LOG = 25;
    vector <vector <int>> anc;
    vector <int> level;

    void SetupLifting(int node, int par) {
        for (int v: T[node]) {
            if(v == par)
                continue;
            anc[v][0] = node;
            level[v] = level[node] + 1;
            for (int k = 1; k < LOG; k++)     
                anc[v][k] = anc[anc[v][k-1]][k-1];
            SetupLifting(v, node);
        }
    }
    LCA_Table(Tree &T, int root = 0): T(T), n(T.n) {
        LOG = 33 - __builtin_clz(n);
        anc.assign(n, vector <int> (LOG, root));
        level.resize(n);
        SetupLifting(root, root);
    }
    int LCA(int u, int v) {
        if (level[u] > level[v])
            swap(u, v);
        for (int k = LOG-1; k >= 0; k--)
            if (level[u] + (1 << k) <= level[v])
                v = anc[v][k];
        if (u == v) 
            return u;
        for (int k = LOG - 1; k >= 0; k--)
            if (anc[u][k] != anc[v][k])
                u = anc[u][k], v = anc[v][k];
        return anc[u][0];
    }
    int GetAnc(int node, int ht) {
        for (int k = 0; k < LOG; k++)
            if (ht & (1 << k))
                node = anc[node][k];
        return node;
    }
    int Dis(int u, int v) {
        int g = LCA(u, v);
        return level[u] + level[v] - 2 * level[g];
    }
};
// USACO yinyangpath
template <typename DT> class c_vector : public vector <DT> {
public:
    using vector <DT> :: vector;  
    using vector <DT> :: begin;
    using vector <DT> :: size;
    DT& operator [] (int _idx) {
        _idx = _idx % int(size());
        size_t idx = _idx + size() * (_idx < 0);
        return idx >= 0 and idx < size() ? *(begin() + idx) : *(begin() + (size() + idx));
    }
    void clear(int l, int r){
        for(int i = l; i <= r; i++)
            (*this)[i] = 0;
    }
};
class Centroid_Decomposition {
    vector <bool> blocked;
    vector <int> CompSize;
    int CompDFS(Tree &T, int node, int par) {
        CompSize[node] = 1;
        for(int &e: T[node]) if(e != par and !blocked[e])
            CompSize[node] += CompDFS(T, e, node);
        return CompSize[node];
    }
    int FindCentroid(Tree &T, int node, int par, int sz) {
        for(int &e: T[node]) if(e != par and !blocked[e]) if(CompSize[e] > sz / 2)
            return FindCentroid(T, e, node, sz);
        return node;
    }
    pair <int,int> GetCentroid(Tree &T, int entry) {
        int sz = CompDFS(T, entry, entry);
        return {FindCentroid(T, entry, entry, sz), sz};
    }
    c_vector <LL> left[2], right[2]; 
    int GMin, GMax;
    void dfs(Tree &T, int node, int par, int Min, int Max, int sum) {
        if(blocked[node])
            return;
        right[Max < sum or Min > sum][sum]++;
        Max = max(Max, sum), Min = min(Min, sum);
        GMin = min(GMin, sum), GMax = max(GMax, sum);
        for(size_t i = 0; i < T[node].size(); i++) if(T[node][i] != par) {
            dfs(T, T[node][i], node, Min, Max, sum + T.col[node][i]);
        }
    }
    LL solve(Tree &T, int c, int sz) {
        LL ans = 0;
        left[0].clear(-sz, sz), left[1].clear(-sz, sz);
        for(size_t i = 0; i < T[c].size(); i++) {
            GMin = 1, GMax = -1;
            dfs(T, T[c][i], c, GMin, GMax, T.col[c][i]);
            ans += right[0][0] + left[1][0] * right[1][0];
            for(int j:{0, 1} ) for(int k = GMin; k <= GMax; k++) {
                ans += right[j][k] * (left[0][-k] + (j == 0) * left[1][-k]);
            }
            for(int j:{0, 1} ) for(int k = GMin; k <= GMax; k++)  {
                left[j][k] += right[j][k];
                right[j][k] = 0;
            }
        }
        return ans;
    }
public:
    LL operator () (Tree &T, int entry) {
        blocked.resize(T.n);
        CompSize.resize(T.n);
        for(int i:{0, 1})
            left[i].resize(2 * T.n + 5), right[i].resize(2 * T.n + 5);
        auto[c, sz] = GetCentroid(T, entry);
        LL ans = solve(T, c, sz);
        blocked[c] = true;
        for(int e: T[c]) if(!blocked[e])
            ans += (*this)(T, e);
        return ans;
    }   
};
int main()
{
    monke_flip
    //freopen("yinyang.in", "r", stdin);
    //freopen("yinyang.out", "w", stdout);
    int n;
    cin >> n;
    Tree T(n);
    // Centroid_Decomposition Decomposer;
    // for(int i = 0, u, v, cl; i < n - 1; i++) {
    //     cin >> u >> v >> cl;
    //     T.AddEdge(u - 1, v - 1, 2 * cl - 1);
    // }
    // cout << Decomposer(T, 0);
    return MONKE;
}