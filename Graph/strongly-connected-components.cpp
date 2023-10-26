#include <bits/stdc++.h>
using namespace std;
using LL = long long;

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

namespace SCC {
    vector <int> order, comp, idx;
    vector <bool> vis;
    vector <vector <int>> comps;
    Graph dag;

    void dfs1(int u, Graph &G, string s = "") {
        vis[u] = 1;
        for(int e: G[u]) {
            int v = G(e).to(u);
            if(!vis[v]) dfs1(v, G, s);
        }
        order.push_back(u);
    }
    void dfs2(int u, Graph &R) {
        comp.push_back(u);
        idx[u] = comps.size();

        for(int e: R[u]) {
            int v = R(e).to(u);
            if(idx[v] == -1) dfs2(v, R);
        }
    }

    void init(Graph &G) {
        int n = G.n;
        vis.assign(n, 0);
        idx.assign(n, -1);

        for(int i = 0; i < n; i++) {
            if(!vis[i]) dfs1(i, G);
        }
        reverse(order.begin(), order.end());
    
        Graph R(n);
        for(auto &e: G.edges) R.addEdge(e.v, e.u, 0);

        for(int u: order) {
            if(idx[u] != -1) continue;
            comp.clear();
            dfs2(u, R);
            comps.push_back(comp);
        }
    }

    Graph& createDAG(Graph &G) {
        int sz = comps.size();
        dag = Graph(sz);

        vector <bool> taken(sz);
        vector <int> cur;

        for(int i = 0; i < sz; i++) {
            cur.clear();
            taken[i] = 1;
            for(int u: comps[i]) {
                for(int e: G[u]) {
                    int v = G(e).to(u);
                    int j = idx[v];
                    if(taken[j]) continue; // rejects multi-edge
                    dag.addEdge(i, j, 0);
                    taken[j] = 1;
                    cur.push_back(j);
                }
            }
            for(int j: cur) taken[j] = 0; 
        }
        return dag;
    }

}

int main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    Graph G(n);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G.addEdge(u, v, 0);
    }

    SCC :: init(G);
    SCC :: createDAG(G);
    using SCC :: comps;

    cout << comps.size() << '\n';
    for(auto &comp : comps) {
        cout << comp.size() << ' ';
        for(int u: comp) {
            cout << u << ' ';
        }
        cout << '\n';
    }

}
