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

using edge = pair <int, int> ;
class Graph {
public:
    int n;
    vector<vector<int>> adj;
    Graph(int n = 0) : n(n), adj(n) {}
    Graph(int n, vector <pair <int,int>> &edges): n(n), adj(n) {
        for(auto &[l,r]:edges)
            add_edge(l, r);
    }
    inline void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    inline int add_node() {
        adj.push_back({});
        return n++;
    }
    inline vector<int>& operator[](int u) { 
        return adj[u]; 
    }
};
class Bridge_Tree {
    int n;
    vector <vector <int>> components;
    vector <int> depth, low;
    stack <int> st;
    void find_bridges(int node, Graph &G, int par = -1, int d = 0) {
        low[node] = depth[node] = d;
        st.push(node);
        for (int e : G[node]) if(par != e) {
            if(depth[e] == -1) {
                find_bridges(e, G, node, d + 1);
                if (low[e] > depth[node]){
                    bridges.emplace_back(node, e);
                    components.push_back({});
                    for(int x = -1; x!= e; x = st.top(), st.pop()) 
                        components.back().push_back(st.top());
                }
            }
            low[node] = min(low[node], low[e]);
        }
        if(par == -1){
            components.push_back({});
            while(!st.empty())
                components.back().push_back(st.top()), st.pop();
        }   
    }
public:
    vector <int> id;
    vector <edge> bridges;
    Graph tree;
    Bridge_Tree(Graph &G): n(G.n) {
        int idx = 0;
        depth.assign(n,-1), id.assign(n, -1), low.resize(n);
        find_bridges(0, G);
        for(auto &comp : components){
            idx = tree.add_node();
            for(auto &e: comp)
                id[e] = idx;
        }
        for(auto &[l,r]: bridges)
            tree.add_edge(id[l], id[r]);
        dbg(components);
    }
};

/*....................................................................*/

void solve() {
    int n, m;
    cin >> n >> m;
    Graph G(n);
    vector <edge> edges(m);
    for(auto &[l,r]:edges){
        cin >> l >> r;
        G.add_edge(l, r);
    }
    Bridge_Tree T(G);
    int ans = 0;
    for(auto &e:T.tree.adj)
        ans += (e.size() == 1);
    cout << (ans + 1 >> 1) << '\n';
}

int main()
{
    monke_flip
    int t = 1;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cout << "Case "<< tc << ": ";
        solve();
    }
    return MONKE;
}