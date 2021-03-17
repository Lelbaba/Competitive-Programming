#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MONKE = 0;
const int maxn = 1e5+5;
class SCC
{
	private:
	vector <bool> vis;
	vector <int> order, component,idx;
	vector <vector <int> > adj, rev,COMPONENTS,DAG;
	vector <set<int> > _DAG;
	void init(int n,vector <pair<int,int> > &edges){
		adj.clear(),rev.clear(), COMPONENTS.clear(),DAG.clear(),_DAG.clear();
		adj.resize(n),rev.resize(n);
		for(auto &e:edges){
			adj[e.first].push_back(e.second);
			rev[e.second].push_back(e.first);
		}
	}
	void dfs1(int node){
		vis[node] = true;
		for(auto x:adj[node]){
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
	public:
	vector <vector <int> > get_SCC(int n,vector <pair<int,int> > &edges){
		init(n,edges);
		vis.assign(n,false);
		order.clear();
		for(int i=0;i<n;i++){
			if(!vis[i]){
				dfs1(i);
			}
		}
		vis.assign(n,false);
		idx.assign(n,0);
		reverse(order.begin(), order.end());
		int i = 0;
		for(auto v:order){
			component.clear();
			if(!vis[v]) dfs2(v);
			if(!component.empty()){
				COMPONENTS.push_back(component);
				for(auto x:component){
					idx[x] = i;
				}
				i++;
			}
		}
		int sz = COMPONENTS.size();
		_DAG.resize(sz), DAG.resize(sz);
		for(auto x:edges){
			_DAG[idx[x.first]].insert(idx[x.second]);
		}
		for(int i=0;i<sz;i++){
			for(auto x:_DAG[i]){
				if(x==i) continue;
				DAG[i].push_back(x);
			}
		}
		return COMPONENTS;
	}
	vector <int> get_idx(){
		return idx;
	}
	vector <vector <int> > get_DAG(){
		return DAG;
	}
} graph;

int main()
{
	int n,m,u,v;
	scanf("%d%d", &n,&m);
	vector <pair<int,int> > edges(m);
	for(auto &e:edges){
		cin>>e.first>>e.second;
	}
	auto com = graph.get_SCC(n,edges);
	for(auto &z:com){
		for(auto x:z) cout<<x<<" ";
		cout<<endl;
	}
	auto dag = graph.get_DAG();

	return MONKE;
}
