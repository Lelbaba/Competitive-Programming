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

/*....................................................................*/ 
template <typename T> class Graph {
public:
    int n;
    struct Edge {
        int u, v;
        T w;
        Edge(int u, int v, T w) : u(u), v(v), w(w) {}
    };
    vector <Edge> edges;
    vector <vector <int>> adj;
    inline int add_node () {
        adj.emplace_back();
        return n++;
    }
    Graph(int n = 0) : n(n), adj(n) {}
    inline int add_edge(int u, int v, T w) {
        adj[u].push_back(edges.size());
        edges.emplace_back(u, v, w);
        return adj[u].back();
    }
    inline vector <int> &operator[](int u) {
        return adj[u];
    }
    inline Edge &operator() (int u){
        return edges[u];
    }
};
template <typename T> class DiGraph : public Graph <T> {
public:
    using Graph <T> :: adj;
    DiGraph(int n) : Graph <T> (n) {}
    inline void add_edge(int u, int v, T w = 0){
        adj[u].push_back(v);
    }
};

template <typename T> bool CycleChecker(DiGraph <T> G){
    vector <char> color(G.n);
    function <bool(int, int)> dfs = [&] (int node, int par){
        color[node] = 1;
        for(int v: G[node])
            if((color[v] == 1) or (!color[v] and dfs(v, node)))
                return true;
        color[node] = 2;
        return false;
    };
    for(int i = 0; i < G.n; i++)
        if(!color[i] and dfs(i, -1))
            return true;
    return false;
}
DiGraph <int> Permutation_Graph(vector <int> &a, vector <int> &b){
    int n = a.size();
    DiGraph <int> G(n);
    for(int i = 0; i < n; i++) 
        G.add_edge(a[i], b[i]);
    return G;
}
int main()
{
	monke_flip
	
	return MONKE;
}