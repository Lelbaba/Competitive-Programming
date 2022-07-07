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
namespace MCMF {
    typedef long long F; typedef double C;
    const F infF = 1e18; const C infC = 1e18;

    const int N = 5005;
    typedef pair<C, F> PCF;

    struct Edge {int frm, to; C cost; F cap, flow;};

    int n, s, t;
    vector<Edge> edges;
    vector<int> adj[N];
    C pi[N], dis[N];
    F fl[N];
    int prv[N], vis[N];

    void init(int nodes, int source, int sink) {
        n = nodes, s = source, t = sink;
        for (int i=0; i<n; i++) pi[i] = 0, adj[i].clear();
        edges.clear();
    }

    void addEdge(int u, int v, F cap,C cost) {
        edges.push_back({u, v, cost, cap, 0});
        edges.push_back({v, u, -cost, 0, 0});
        adj[u].push_back(edges.size()-2);
        adj[v].push_back(edges.size()-1);
    }

    bool SPFA() {
        for (int i=0; i<n; i++) {
            dis[i] = infC; fl[i] = 0;
            vis[i] = 0; prv[i] = -1;
        }
        queue<int> q;
        q.push(s);
        dis[s] = 0; fl[s] = infF; vis[s] = 1;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for (int eid : adj[u]) {
                Edge &e = edges[eid];
                if (e.cap == e.flow) continue;

                if (dis[u] + e.cost < dis[e.to]) {
                    dis[e.to] = dis[u] + e.cost;
                    fl[e.to] = min(fl[u], e.cap - e.flow);
                    prv[e.to] = eid^1;
                    if (!vis[e.to])     q.push(e.to);
                }
            }
        }
        return fl[t] > 0;
    }

    PCF solveSPFA() {
        C cost = 0; F flow = 0;
        while (SPFA()) {
            C pathcost = dis[t];
            cost += pathcost*fl[t]; flow += fl[t];
            for (int u=t, e=prv[u]; e!=-1; u=edges[e].to, e=prv[u]) {
                edges[e].flow -= fl[t];
                edges[e^1].flow += fl[t];
            }
        }
        return {cost, flow};
    }

    void normalize() {
        SPFA();
        for (int i=0; i<n; i++) pi[i] = dis[i];
    }

    bool Dijkstra() {
        for (int i=0; i<n; i++) {
            dis[i] = infC; fl[i] = 0;
            vis[i] = 0; prv[i] = -1;
        }
        priority_queue<pair<C, int>> pq;
        pq.emplace(0, s);
        dis[s] = 0; fl[s] = infF;

        while (!pq.empty()) {
            int u = pq.top().second; pq.pop();
            if (vis[u]) continue;
            vis[u] = 1;

            for (int eid : adj[u]) {
                Edge &e = edges[eid];
                if (vis[e.to] || e.cap == e.flow) continue;

                C nw = dis[u] + e.cost - pi[e.to] + pi[u];
                if (nw < dis[e.to]) {
                    dis[e.to] = nw;
                    fl[e.to] = min(fl[u], e.cap - e.flow);
                    prv[e.to] = eid^1;
                    pq.emplace(-dis[e.to], e.to);
                }
            }
        }
        return fl[t] > 0;
    }

    PCF solveDijkstra() {
        normalize();
        C cost = 0; F flow = 0;
        while (Dijkstra()) {
            for (int i=0; i<n; i++)
                if (fl[i])     pi[i] += dis[i];
            C pathcost = pi[t]-pi[s];
            cost += pathcost*fl[t]; flow += fl[t];

            for (int u=t, e=prv[u]; e!=-1; u=edges[e].to, e=prv[u]) {
                edges[e].flow -= fl[t];
                edges[e^1].flow += fl[t];
            }
        }
        return {cost, flow};
    }
}
// want to minimize cost and don't care about flow
// add edge from sink to dummy sink (cap = inf, cost = 0)
// add edge from source to sink (cap = inf, cost = 0)
// run mcmf, cost returned is the minimum cost

/*....................................................................*/

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector <double> p(k + 1), d(k + 1);
    vector <int> book(n + 1);

    for(int i = 1; i <= k; i++) 
        cin >> p[i];
    for(int i = 1; i <= k; i++) 
        cin >> d[i];
    for(int i = 1; i <= n; i++)
        cin >> book[i];

    double lo = 0, hi = 1;
    for(int _ = 0; _ < 100; _++) {
        double mid = lo + (hi - lo) / 2;
        MCMF :: init(n + 2, 0, n + 1);

        for(int i = 1; i < n; i++)  
            MCMF :: addEdge(i, i + 1, m - 1, 0.);

        vector <int> last(k + 1);
        for(int i = 1; i <= n; i++){
            int b = book[i];
            MCMF :: addEdge(last[b], i, 1, p[b] - d[b]);
            if(last[b])  MCMF :: addEdge(0, last[b], 1, 0.);
            MCMF :: addEdge(i, n + 1, 1, -p[b] * mid);
            last[b] = i;
        }
        auto [mc, mf] = MCMF :: solveDijkstra();
        assert(mf == n);
        if(mc < 0) hi = mid;
        else lo = mid;
    }
    cout << fixed << setprecision(10) << lo * 100 << '\n';
}

int main()
{
    monke_flip
    int t = 1;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        solve();
    }
    return MONKE;
}