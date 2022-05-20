#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using edge = pair <LL,LL>;
class Djikstra{
public:
	LL n = -1;
	vector <vector <edge> > adj;
	vector <LL> D,path;
	Djikstra(vector < vector <edge> > &A,LL x){
		n = A.size();
		adj = A;
		D.assign(n,LLONG_MAX);
		path.assign(n,-1);
		find_shortest_paths(x);
	}
	void find_shortest_paths(LL s) {
		priority_queue < edge, vector <edge>, greater<edge> > Q;
		Q.emplace(0,s);
		while(!Q.empty()){

			LL node = Q.top().second, d = Q.top().first;
			Q.pop();
			if(d>D[node]) continue;
			D[node] = d; 
			for(auto e:adj[node]){
				LL _next = e.second, dis = e.first;
				if(D[_next]>dis+d){
					D[_next] = dis+d;
					path[_next] = node;
					Q.emplace(dis+d,_next);
				}
			}
		}
	}

};
int main()
{
	int n,m;
	cin>>n>>m;
	vector <vector <edge> > adj(n);
	for(int i=0;i<m;i++){
		LL u,v,w;
		cin>>u>>v>>w;
		adj[u-1].emplace_back(w,v-1);
		adj[v-1].emplace_back(w,u-1);
	}
	Djikstra G(adj,0);
	int r = n-1;
	if(G.path[r]==-1){
		cout<<-1;
	} else{
		vector <int> ans;
		while(r>=0){
			ans.push_back(r+1);
			r = G.path[r];
		}
		reverse(ans.begin(), ans.end());
		for(auto x:ans)	cout<<x<<" ";
	}
	return 0;
}
