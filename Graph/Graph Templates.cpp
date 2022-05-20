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
template <typename T> class WtGraph {
public:
    int n;
    struct Edge {
        int u, v;
        T w;
        Edge(int u, int v, T w) : u(u), v(v), w(w) {}
    };
    vector <Edge> edges;
    vector <vector <int>> adj; // adj contains id of edge

    WtGraph(int n = 0) : n(n), adj(n) {}
    inline int add_edge(int u, int v, T w) {
        adj[u].push_back(edges.size());
        edges.emplace_back(u, v, w);
        adj[v].push_back(edges.size());
        edges.emplace_back(v, u, w);
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
class DiGraph {
public:
    int n;
    vector <vector <int>> adj;
    DiGraph(int n = 0) : n(n), adj(n) {}
    inline int add_node () {
        adj.emplace_back();
        return n++;
    }
    inline vector <int> &operator[](int u) {
        return adj[u];
    }
    inline void add_edge(int u, int v){
        adj[u].push_back(v);
    }
};
class Graph {
public:
    int n;
    vector <vector <int>> adj;
    Graph(int n = 0) : n(n), adj(n) {}
    inline int add_node () {
        adj.emplace_back();
        return n++;
    }
    inline vector <int> &operator[](int u) {
        return adj[u];
    }
    inline void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};
