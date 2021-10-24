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
const int INF = 1e9;
class mcf_graph {
    int n;
    vector <vector <int>> adj, cost, capacity;
    vector <int> d, p;
    bool shortest_paths(int s, int t) {
        vector<bool> inq(n, false);
        queue<int> q;

        for (q.push(s); !q.empty(); ) {
            int u = q.front();
            q.pop(), inq[u] = false;
            for (int v : adj[u]) {
                if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                    d[v] = d[u] + cost[u][v], p[v] = u;
                    if (!inq[v]) 
                        inq[v] = true, q.push(v);
                }
            }
        }
        return d[t] < INF;
    }
public:
    mcf_graph(int n) : n(n), adj(n), cost(n, vector <int>(n)), capacity(n, vector <int>(n)), d(n, INF), p(n,-1) {} 
    int min_cost_flow(int K, int s, int t) {
        int flow = 0, cost = 0;
        for (; flow < K  and shortest_paths(s, t); d.assign(n, INF), d[s] = 0, p.assign(n, -1)) {
            
            int f = K - flow, cur = t;
            for (; cur != s; cur = p[cur]) 
                f = min(f, capacity[p[cur]][cur]);

            flow += f, cost += f * d[t], cur = t;
            
            for (; cur != s; cur = p[cur]) 
                capacity[p[cur]][cur] -= f, capacity[cur][p[cur]] += f;
        }
        return flow < K ? -1: cost;
    }
    void add_edge(int u, int v, int cap, int cs) {
        adj[u].push_back(v), adj[v].push_back(u), capacity[u][v] = cap, cost[u][v] = cs, cost[v][u] = -cs;
    }
};
/*....................................................................*/ 

int main()
{
    monke_flip
    
    return MONKE;
}