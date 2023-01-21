#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v;
    edge(int u = 0, int v = 0) : u(u), v(v) {}
    int to(int node){
        return u ^ v ^ node;
    }
};
struct graph {
    int n;
    vector<vector<int>> adj;
    vector <edge> edges;
    graph(int n = 0) : n(n), adj(n) {}
    void addEdge(int u, int v, bool dir = 1) {
        adj[u].push_back(edges.size());
        if(dir) adj[v].push_back(edges.size());
        edges.emplace_back(u, v);
    }
    int addNode() {
        adj.emplace_back();
        return n++;
    }
    edge &operator()(int idx) { return edges[idx]; }
    vector<int> &operator[](int u) { return adj[u]; }
};
/*
This block-cut tree is for connected graphs
corners:
1. only 1 node
2. 2 nodes with 1 edge
*/
namespace block_cut_tree {
    vector < vector <int> > components;
    vector <int> cutpoints, start, low;
    vector <bool> is_cutpoint;
    stack <int> st;
    void find_cutpoints(int node, graph &G, int par = -1, int d = 0){
        low[node] = start[node] = d++;
        st.push(node);
        int cnt = 0;
        for(int e: G[node]) if(int to = G(e).to(node); to != par) {
            if(start[to] == -1){
                find_cutpoints(to, G, node, d+1);
                cnt++;
                if(low[to]  >= start[node]){
                    is_cutpoint[node] = par != -1 or cnt > 1;
                    components.push_back({node}); // starting a new block with the point
                    while(st.top() != node)
                        components.back().push_back(st.top()), st.pop();    
                }
            }
            low[node] = min(low[node], low[to]);
        }
        
    }
    graph tree;
    vector <int> id;
    void init(graph &G) {
        int n = G.n;
        start.assign(n, -1), low.resize(n), is_cutpoint.resize(n), id.assign(n, -1);
        find_cutpoints(0, G);
        for (int u = 0; u < n; ++u)
            if (is_cutpoint[u]) 
                id[u] = tree.addNode();
        for (auto &comp : components) {
            int node = tree.addNode();
            for (int u : comp)
                if (!is_cutpoint[u]) id[u] = node;
                else tree.addEdge(node, id[u]);
        }
        if(id[0] == -1) // corner - 1
            id[0] = tree.addNode();
    }
};
int main() {

}
