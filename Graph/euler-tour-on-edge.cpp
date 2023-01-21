#include <bits/stdc++.h>
using namespace std;
using LL = long long;
// solves codechef PSHTTR
// this implementation of the graph structure is general and easily modifiable
// for simplicity, G[idx] contains the adjacency list of a node
// while G(e) is a reference to the e-th edge.
struct edge {
    int u, v;
    edge(int u, int v) : u(u), v(v) {}
    int to(int node) { 
        return node ^ u ^ v;
    }
};
struct graph {
    int n, e = 0;
    vector <vector <int>> adj;
    vector <edge> edges;
    int addEdge(int u, int v, bool bi = 1) {
        edges.emplace_back(u, v);
        adj[u].push_back(e);
        if(bi) adj[v].push_back(e);
        return e++;
    }
    int addNode() {
        adj.emplace_back();
        return n++;
    }
    vector <int>& operator [](int idx) {
        return adj[idx];
    }
    edge& operator () (int id){
        return edges[id];
    }
    graph(int n = 0) : n(n), adj(n) {}
};
namespace et_edge {
    const int N = 2e5 + 5;
    int in[N], out[N], fwd[N], bck[N];
    int t = 0;
    void dfs(graph &G, int node, int par) {
        out[node] = t; 
        for(int e: G[node]) {
            int v = G(e).to(node);
            if(v == par) continue;
            fwd[e] = t++;
            dfs(G, v, node);
            bck[e] = t++;
        }
        in[node] = t - 1;
    }
    void init(graph &G, int node) {
        t = 0;
        dfs(G, node, node);
    }
}
namespace BIT {
    const int N = 2e5 + 5;
    using DT = long long;
    int n;
    DT tree[N]; 
    void init(int _n) {
        n = _n;
        fill(tree, tree + n, 0);
    }
    DT query(int r) {
        DT ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1) ret ^= tree[r];
        return ret;
    }
    DT query(int l, int r) {
        return query(r) ^ query(l - 1);
    }
    void update(int idx, DT delta) {
        for (; idx < n; idx = idx | (idx + 1)) tree[idx] ^= delta;
    }
};

int main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        graph G(n);
        map <LL, vector <int>> edgelist;
        for(int i = 0, u, v; i + 1 < n; i++) {
            LL c;
            cin >> u >> v >> c;
            u--, v--;
            edgelist[c].push_back(G.addEdge(u, v));
        }
        et_edge :: init(G, 0);
        BIT :: init(2 * n);
        int q;
        cin >> q; 
        vector <int> _u(q), _v(q), id(q); 
        vector <LL> _k(q), ans(q); 
        for(int i = 0; i < q; i++) {
            cin >> _u[i] >> _v[i] >> _k[i];
            _u[i]--, _v[i]--;
        }
        iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](int x, int y){ return make_pair(_k[x], x) < make_pair(_k[y], y); });
        auto it = edgelist.begin();
        for(int i : id) {
            while(it != edgelist.end() and it -> first <= _k[i]) {
                for(int j: it -> second) {
                    BIT :: update(et_edge :: fwd[j], it -> first);
                    BIT :: update(et_edge :: bck[j], it -> first);
                }
                it++;
            }
            int ui = et_edge :: in[_u[i]], uo = et_edge :: out[_u[i]], vi = et_edge :: in[_v[i]], vo = et_edge :: out[_v[i]];
            ans[i] = uo < vi ? BIT :: query(uo, vi) : BIT :: query(vo, ui);
        }
        for(LL e: ans) cout << e << '\n';
    }
}
