#include <bits/stdc++.h>
using namespace std;
struct edge {
    int u, v, w;
    edge(int u, int v, int w) : u(u), v(v), w(w) {}
    int nxt(int node) { 
        return node ^ u ^ v;
    }
};
struct graph {
    int n, e = 0;
    vector <vector <int>> adj;
    vector <edge> edges;
    int addEdge(int u, int v, int w, bool bi = 1) {
        edges.emplace_back(u, v, w);
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
namespace bcc {
	const int N = 2e5 + 5;
	vector <int> comps[N];
	vector <int> Tree[N];
	int low[N], st[N], id[N], eid[N];
	bool is_cut[N];
	int t = 0, sz = 0;
	stack <int> bag;
	void addEdge(int u, int v) {
		Tree[u].push_back(v);
		Tree[v].push_back(u);
	}
	void dfs(graph &G, int node, int par = -1) {
		low[node] = st[node] = ++t;
		int cnt = 0;
		for(int e: G[node]) {
			int to = G(e).nxt(node);
			if(to == par) continue;
			if(st[to] < st[node]) bag.push(e);
			if(st[to]) {
				low[node] = min(low[node], st[to]);
				continue;
			}
			cnt++;
			dfs(G, to, node);
			low[node] = min(low[node], low[to]);
			if(low[to] >= st[node]) {
				is_cut[node] = par != -1 or cnt > 1;
				for(int z = -1; z != e; bag.pop()) {
					comps[sz].push_back(z = bag.top());
					auto &ce = G(e);
					eid[z] = sz;
				}
				sz++;
			}
		}
		if(is_cut[node]) id[node] = sz++;
	}
	void init(graph &G, int root = 0) {
		memset(eid, -1, sizeof eid);
		memset(id, -1, sizeof id);
		dfs(G, root);
		int idx = 0;
		for(auto &ce: G.edges) {
			if(is_cut[ce.u]) addEdge(eid[idx], id[ce.u]);
			else id[ce.u] = eid[idx];
			if(is_cut[ce.v]) addEdge(eid[idx], id[ce.v]);
			else id[ce.v] = eid[idx];
			idx++;
		}
	}
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n, m, s, t;
	cin >> n >> m;
	graph G(n);
	for(int i = 0, u, v, w; i < m; i++) {
		cin >> u >> v >> w;
		G.addEdge(u, v, w);
	}
	bcc :: init(G);
}