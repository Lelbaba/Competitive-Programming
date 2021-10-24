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
const LL INF = 1ll << 60;
struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};
class Dinic {
    vector <FlowEdge> edges;
    vector <vector <int>> adj;
    int n, m = 0;
    vector <int> level, ptr;
    queue <int> q;
    bool bfs(int t) {
        for (; !q.empty(); q.pop()) {
            for (int id : adj[q.front()]){
                auto &[v, u, cap, flow] = edges[id];
                if (cap - flow > 0 and level[u] == -1) {
                    level[u] = level[v] + 1;
                    q.push(u);
                }
            }
        }
        return level[t] != -1;
    }

    LL dfs(int v, LL pushed, int t) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            auto &[cur, u, cap, flow] = edges[id];
            if (level[v] + 1 != level[u] || cap - flow < 1)
                continue;
            LL tr = dfs(u, min(pushed, cap - flow), t);
            if (tr == 0)
                continue;
            flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }
public:
    Dinic(int n) : n(n), adj(n), level(n, -1), ptr(n) {}
    void add_edge(int v, int u, LL cap) {
        edges.emplace_back(v, u, cap), adj[v].push_back(m);
        edges.emplace_back(u, v, 0), adj[u].push_back(m + 1);
        m += 2;
    }
    LL maxflow(int s, int t) {
        LL f = 0;
        for(auto &[v, u, cap, flow]: edges)
            flow = 0;
        for (level[s] = 0, q.push(s); bfs(t); fill(level.begin(), level.end(), -1), level[s] = 0, q.push(s)) {
            for (fill(ptr.begin(), ptr.end(), 0); LL pushed = dfs(s, INF, t); f += pushed);
        }
        return f;
    }
};
/*....................................................................*/ 

int main()
{
    monke_flip
    
    return MONKE;
}