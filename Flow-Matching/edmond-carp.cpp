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

/*....................................................................*/

const LL INF = 1ll << 60;
class Edmonds_Carp {
    int n;
    vector <vector <int>> adj;
    vector <vector <LL>> capacity, flow;
    vector<int> prev;

    LL bfs(int s, int t) {
        fill(prev.begin(), prev.end(), -1);
        prev[s] = -2;
        queue< pair <int, LL>> q;
        for (q.emplace(s, INF); !q.empty(); q.pop()) {
            auto [cur, Flow] = q.front();
            for (int next : adj[cur]) {
                LL new_flow = capacity[cur][next] - flow[cur][next];
                if (prev[next] == -1 and new_flow) {
                    prev[next] = cur;
                    new_flow = min(Flow, new_flow);
                    if (next == t)
                        return new_flow;
                    q.emplace(next, new_flow);
                }
            }
        }
        return 0ll;
    }

public:
    Edmonds_Carp(int n) : n(n), adj(n), capacity(n, vector <LL>(n)), prev(n), flow(n, vector <LL> (n)) {};

    void add_edge(int u, int v, LL cap) {
        adj[u].push_back(v), adj[v].push_back(u);
        capacity[u][v] += cap;
    }
    LL maxflow(int s, int t) {
        LL Flow = 0;
        for (LL new_flow = bfs(s, t); new_flow != 0; Flow += new_flow, new_flow = bfs(s, t)) {
            for (int cur = t ;cur != s; cur = prev[cur]) {
                flow[prev[cur]][cur] += new_flow;
                flow[cur][prev[cur]] -= new_flow;
            }
        }
        return Flow;
    }
    vector<int>& operator[] (int u) { 
        return adj[u];
    }
    LL check_flow(int u, int v) {
        return flow[u][v];
    }
};

int main()
{
    monke_flip

    return MONKE;
}