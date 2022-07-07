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
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
// Order Statistic Tree

/* Special functions:
        find_by_order(k) --> returns iterator to the kth largest element counting from 0
        order_of_key(val) --> returns the number of items in a set that are strictly smaller than our item
*/

/*....................................................................*/ 

namespace Dinic {
    typedef long long LL;
    const int N = 5005, K = 60; /// N > no of nodes, K >= max bits in capacity
    const LL INF = 1e18;

    struct Edge { int frm, to; LL cap, flow; };

    int s, t, n;
    int level[N], ptr[N];
    vector<Edge> edges;
    vector<int> adj[N];

    void init(int nodes) {
        n = nodes;
        for (int i=0; i<n; i++)    adj[i].clear();
        edges.clear();
    }

    /// For adding undirected Edge (u, v, c) call addEdge(u, v, c, c);
    int addEdge(int a, int b, LL cap, LL revcap = 0) {
        edges.push_back({a, b, cap, 0});
        edges.push_back({b, a, revcap, 0});
        adj[a].push_back(edges.size()-2);
        adj[b].push_back(edges.size()-1);
        return edges.size()-2;
    }

    bool bfs(LL lim) {
        fill(level, level+n, -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty() && level[t] == -1) {
            int v = q.front();
            q.pop();
            for (int id: adj[v]) {
                Edge e = edges[id];
                if (level[e.to] == -1 && e.cap - e.flow >= lim) {
                    q.push(e.to);
                    level[e.to] = level[v] + 1;
                }
            }
        }
        return level[t] != -1;
    }
    LL dfs(int v, LL flow) {
        if (v == t || !flow)        return flow;
        for (; ptr[v] < adj[v].size(); ptr[v]++) {
            int eid = adj[v][ptr[v]];
            Edge &e = edges[eid];
            if (level[e.to] != level[v] + 1)    continue;
            if (LL pushed = dfs(e.to, min(flow, e.cap - e.flow))) {
                e.flow += pushed;
                edges[eid^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
    LL maxFlow(int source, int sink, bool SCALING = false) {
        s = source, t = sink;

        long long flow = 0;
        for (LL lim = SCALING ? (1LL << K) : 1; lim > 0; lim >>= 1) {
            while (bfs(lim)) {
                fill(ptr, ptr+n, 0);
                while (LL pushed = dfs(s, INF)) flow += pushed;
            }
        }
        return flow;
    }

    bool leftOfMinCut(int x) {return level[x] != -1;}

    /// Only works for undirected graph, Make sure to add UNDIRECTED edges. (u, v, c, c)
    /// returns n by n matrix flow, st flow[i][j] = maxFlow
    /// tree holds the edges of a gomory-hu tree of the graph
    vector<vector<LL>> allPairMaxFlow(vector<Edge> &tree) {
        tree.clear();
        vector<vector<LL>> flow(n, vector<LL> (n, INF));

        vector<int> par(n);
        for (int i=1; i<n; i++) {
            for (auto &e: edges)    e.flow = 0;
            LL f = maxFlow(i, par[i]);
            tree.push_back({i, par[i], f});

            for (int j=i+1; j<n; j++)
                if (par[j] == par[i] && leftOfMinCut(j)) par[j] = i;

            flow[i][par[i]] = flow[par[i]][i] = f;
            for (int j=0; j<i; j++)
                if (j != par[i])    flow[i][j] = flow[j][i] = min(f, flow[par[i]][j]);
        }
        return flow;
    }
}

/*....................................................................*/ 
int main()
{
    monke_flip
    int n;
    cin >> n;
    vector <pair <int, int>> v(n);
    vector <int> vals;
    for(auto &[x, y]: v)  {
        cin >> x >> y;
        vals.push_back(x + y);
        vals.push_back(x - y);
        vals.push_back(x * y);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    dbg(vals);
    map <int, int> Nodes;
    int N = n;
    for(auto e: vals) Nodes[e] = N++;
    dbg(Nodes);
    int S = N++, T = N++;
    Dinic :: init(N);
    map <pair <int, int>, int> edge;
    vector <map <string, int>> EE(n);
    auto &EDG = Dinic :: edges;
    for(int i = 0; i < n; i++) {
        auto [x, y] = v[i];
        dbg(x, y);
        dbg(Nodes[x - y]);
        EE[i][" + "] = Dinic :: addEdge(i, Nodes[x + y], 1);
        EE[i][" - "] = Dinic :: addEdge(i, Nodes[x - y], 1);
        EE[i][" * "] = Dinic :: addEdge(i, Nodes[x * y], 1);
        Dinic :: addEdge(S, i, 1);
    }
    for(int i = 0; i < vals.size(); i++) 
        Dinic :: addEdge(n + i, T, 1);
    if(Dinic :: maxFlow(S, T) < n) cout << "impossible\n";
    else {
        for(int i = 0; i < n; i++) {
            for(auto &[op, ed] : EE[i]) {
                if(EDG[ed].flow){
                    cout << v[i].first << op << v[i].second << " = " << vals[EDG[ed].to - n] << '\n';
                    break;
                }
            }
        }
    }
    return MONKE;
}
