#include <bits/stdc++.h>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#ifdef LEL
#include "dbg.h"
#else
#define dbg(...) {/* temon kichu na; */}
#endif
using namespace std;
using LL = long long;
const int MONKE = 0;

//untested 
class Graph {
public:
    int n;
    vector<vector<int>> adj;
    Graph(int n = 0) : n(n), adj(n) {}
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
class top_sort{
public:
	int n;
	vector <int> in, order;
	top_sort(Graph &G): n(G.n), in(G.n) {
		for(auto &A: G.adj) 
			for(int &e: A) 
				in[e]++;

		queue <int> q;
		order.clear();
		for(int i = 0; i < n; i++) if(!in[i]) 
			q.push(i);
		for(;!q.empty(); q.pop()){
			auto t = q.front();
			order.push_back(t);
			for(auto v: G[t])
				if(--in[v] == 0)
					q.push(v);
		}
	}
};

int main()
{

	return MONKE;
}