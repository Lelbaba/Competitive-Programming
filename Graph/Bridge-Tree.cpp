#include <bits/stdc++.h>
using namespace std;
using LL = long long;

/*
    Working bridge tree for non-simple graphs
    https://judge.yosupo.jp/submission/152794
*/

struct Edge {
    int u, v;
    Edge(int _u = 0, int _v = 0) : u(_u), v(_v) {}
    int to(int node){
        return u ^ v ^ node;
    }
};

struct Graph {
    int n;
    vector <vector<int>> adj;
    vector <Edge> edges;
    Graph(int _n = 0) : n(_n), adj(_n) {}
    void addEdge(int u, int v, bool dir = 1) {
        adj[u].push_back(edges.size());
        if(dir) adj[v].push_back(edges.size());
        edges.emplace_back(u, v);
    }
    int addNode() {
        adj.emplace_back();
        return n++;
    }
    Edge &operator()(int idx) { return edges[idx]; }
    vector<int> &operator[](int u) { return adj[u]; }
};

namespace BT {
    vector <vector <int>> comps;
    vector <int> depth, low, id;
    stack <int> st;
    vector <Edge> bridges;
    Graph tree;

    void dfs(int u, Graph &G, int ed = -1, int d = 0) {
        low[u] = depth[u] = d;
        st.push(u);

        for (int e : G[u]) {
            if(e == ed) continue;
            int v = G(e).to(u);
            if (depth[v] == -1) dfs(v, G, e, d + 1); 
            low[u] = min(low[u], low[v]);
            
            if(low[v] <= depth[u]) continue;
            bridges.emplace_back(u, v);
            comps.emplace_back();
            do {
                comps.back().push_back(st.top()), st.pop();
            } while(comps.back().back() != v);
        }

        if (ed == -1) {
            comps.emplace_back();
            while (!st.empty()) comps.back().push_back(st.top()), st.pop();
        }
    }

    Graph &createTree() {
        for (auto &comp : comps) {
            int idx = tree.addNode();
            for (auto &e : comp) id[e] = idx;
        }

        for (auto &[l, r] : bridges) tree.addEdge(id[l], id[r]);
        return tree;
    }

    void init(Graph &G) {
        int n = G.n;
        depth.assign(n, -1), id.assign(n, -1), low.resize(n);

        for (int i = 0; i < n; i++){
            if (depth[i] == -1) dfs(i, G);
        }
    }
}

using Tree = Graph;
int main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    Graph G(n);
    vector <Edge> edges(m);

    for(auto &[u, v]: edges) {
        cin >> u >> v;
        G.addEdge(u, v);
    }

    BT :: init(G);
    Tree T = BT :: createTree();
    using BT :: comps;
    
    cout << comps.size() << '\n';
    for(auto &c: comps) {
        cout << c.size() << ' ';
        for(int u: c) cout << u << ' ';
        cout << '\n';
    }
}
