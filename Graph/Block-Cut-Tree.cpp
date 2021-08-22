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

/*
This block-cut tree is for connected graphs
corners:
1. only 1 node
2. 2 nodes with 1 edge
*/
class BlockCut_Tree{
    int n;
    vector < vector <int> > components;
    vector <int> cutpoints, start, low;
    vector <bool> is_cutpoint;
    stack <int> st;
    void find_cutpoints(int node, Graph &G, int par = -1, int d = 0){
        low[node] = start[node] = d++;
        st.push(node);
        int cnt = 0;
        for(int e:G[node]) if(e != par) {
            if(start[e] == -1){
                find_cutpoints(e, G, node, d+1);
                cnt++;
                if(low[e]  >= start[node]){
                    is_cutpoint[node] = par != -1 or cnt > 1;
                    components.push_back({node}); // starting a new block with the point
                    while(st.top() != node)
                        components.back().push_back(st.top()), st.pop();    
                }
            }
            low[node] = min(low[node], low[e]);
        }
        
    }
public:
    Graph tree;
    vector <int> id;
    BlockCut_Tree(Graph &G): n(G.n) {
        start.assign(n, -1), low.resize(n), is_cutpoint.resize(n), id.assign(n, -1);
        find_cutpoints(0, G);
        for (int u = 0; u < n; ++u)
            if (is_cutpoint[u]) 
                id[u] = tree.add_node();
        for (auto &comp : components) {
            int node = tree.add_node();
            for (int u : comp)
                if (!is_cutpoint[u]) id[u] = node;
                else tree.add_edge(node, id[u]);
        }
        dbg(components);
        if(id[0] == -1) // corner - 1
            id[0] = tree.add_node();
    }
};