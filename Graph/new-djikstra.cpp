template <typename TYPE> class djikstra {
    using edge = pair <TYPE, int> ;
    int n;
    vector <vector <edge> > adj;
    vector <TYPE> D;
    vector <int> path;
    TYPE Z, MAX;
public:
    djikstra(vector < vector <edge> > &A, TYPE MAX, TYPE Z) : n(A.size()), adj(A), Z(Z), MAX(MAX) {
        D.assign(n, MAX);
        path.assign(n, -1);
    }
    vector <TYPE> find_shortest_paths(int s) {
        priority_queue < edge, vector <edge>, greater<edge> > Q;
        Q.emplace(Z, s);
        while (!Q.empty()) {
            auto [d, node] = Q.top();
            Q.pop();
            if (d > D[node]) continue;
            D[node] = d;
            for (auto &[dis, _next] : adj[node]) {
                if (D[_next] > dis + d) {
                    D[_next] = dis + d;
                    path[_next] = node;
                    Q.emplace(dis + d, _next);
                }
            }
        }
        return D;
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