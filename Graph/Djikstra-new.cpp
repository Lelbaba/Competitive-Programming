template <typename T> class WtDiGraph {
public:
    int n;
    struct Edge {
        int u, v;
        T w;
        Edge(int u, int v, T w) : u(u), v(v), w(w) {}
    };
    vector <Edge> edges;
    vector <vector <int>> adj; // adj contains id of edge

    WtDiGraph(int n = 0) : n(n), adj(n) {}
    inline int add_edge(int u, int v, T w) {
        adj[u].push_back(edges.size());
        edges.emplace_back(u, v, w);
        return adj[u].back();
    }
    inline int add_node () {
        adj.emplace_back();
        return n++;
    }
    inline vector <int> &operator[](int u) {
        return adj[u];
    }
    inline Edge &operator() (int u){
        return edges[u];
    }
};
const LL inf = 1e18;

template <typename T, typename Graph> class Djikstra{
using edge = pair <LL,LL>;
public:
    vector <T> Dis;
    vector <int> path;

    void find_shortest_paths(Graph &G, int node) {
        using edge = pair <LL, LL>;
        int n = G.n;
        Dis.assign(n, inf);
        path.assign(n, -1);
        priority_queue < edge, vector <edge>, greater <edge> > Q;
        for(Q.emplace(0, node); !Q.empty(); Q.pop()) {
            auto [node, d] = Q.top();
            if(d > Dis[node])
                continue;
            Dis[node] = d;
            for(auto e: G[node]) {
                auto [u, v, w] = G(e);
                if(Dis[v] > d + w){
                    Dis[v] = d + w;
                    path[v] = node;
                    Q.emplace(Dis[v]);
                } 
            }
        }
    }
    vector < int > get_path(int s, int e) {
        // should call find_shortest_path(s) first
        vector <int > ans;
        for ( ; e != -1; e = path[e] )
            ans.push_back(e);
        reverse(ans.begin(), ans.end() );
        return ans;
    }

};