#include <bits/stdc++.h>
using namespace std;


struct graph
{
	int n;
	vector <int> t_in;
	vector <int> low;
	vector <bool> vis;
	vector <int> cut_points;
	int timer = 0;
	vector< vector <int> > edges;
	void innit(){
		t_in.resize(n);
		low.resize(n);
		vis.resize(n,false);
		timer = 0;
	}

}g1;


void dfs(int u,int p){
	g1.timer++;
	g1.t_in[u] = g1.timer;
	g1.low[u] = g1.timer+1;
	g1.vis[u] = true;
	int children = 0;
	for(auto v: g1.edges[u]){
		if(v==p) continue;
		if(!g1.vis[v]){ 
			dfs(v,u);
			g1.low[u] = min(g1.low[u],g1.low[v]);
		}
		else g1.low[u] = min(g1.low[u],g1.t_in[v]);
		children++;
	}
	if(p==-1){
		if(children>1) g1.cut_points.push_back(u);
	} 
	else if(g1.low[u]>=g1.t_in[u]) g1.cut_points.push_back(u);
}

int main()
{
	int m;
	cin>>g1.n>>m;
	g1.edges.resize(g1.n);
	for(int i=0;i<m;i++){
		int u,v;
		cin>>u>>v;
		u--;v--;
		g1.edges[u].push_back(v);
		g1.edges[v].push_back(u);
	}
	g1.innit();
	dfs(0,-1);
	//for(auto x:g1.edges[4]) cout<<x<<endl;
	for(auto x:g1.cut_points) cout<<x<<" "<<g1.t_in[x]<<" "<<g1.low[x]<<endl;
	return 0;
}