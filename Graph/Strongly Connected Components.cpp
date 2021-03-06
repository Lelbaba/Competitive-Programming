#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MONKE = 0;
const int maxn = 1e5+5;

vector <vector <int> > edge, rev;
vector <bool> vis;
vector <int> order, component;

void dfs1(int node){
	vis[node] = true;
	for(auto x:edge[node]){
		if(!vis[x]) dfs1(x);
	}
	order.push_back(node);
}

void dfs2(int node){
	vis[node] = true;
	component.push_back(node);
	for(auto x:rev[node]){
		if(!vis[x]) dfs2(x);
	}
}
void input(int &n){
	int m,u,v;
	scanf("%d%d", &n,&m);
	edge.clear(),rev.clear();
	edge.resize(n),rev.resize(n);
	for(int i=0;i<m;i++){
		scanf("%d%d", &u,&v);
		edge[u].push_back(v);
		rev[v].push_back(u);
	}
}
vector <vector <int> > SCC(int n){
	vis.assign(n,false);
	order.clear();
	for(int i=0;i<n;i++){
		if(!vis[i]){
			dfs1(i);
		}
	}
	vis.assign(n,false);
	reverse(order.begin(), order.end());
	vector <vector <int> > COMPONENTS;
	for(auto v:order){
		component.clear();
		if(!vis[v]) dfs2(v);
		if(!component.empty())
			COMPONENTS.push_back(component);
	}
	return COMPONENTS;
}

int main()
{
	int n;
	input(n);
	auto com = SCC(n);
	for(auto &z:com){
		for(auto x:z) cout<<x<<" ";
		cout<<endl;
	}
	return MONKE;
}
