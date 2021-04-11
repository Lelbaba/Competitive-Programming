#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair <long long,int>;

const int MONKE = 0;
/*
In this ques the k-th shortest path might be equal to the shortest path as well assuming k paths are equally short
some varients may require that n-th shortest path>(n-1)-th shortest path
*/

void K_shortest(int n,int m){
	int st,des,k,u,v;
	ll w;
	scanf("%d%d%d", &st,&des,&k);
	st--,des--;
	vector <vector<pii > > edges(n);
	for(int i=0;i<m;i++){
		scanf("%d%d%lld", &u,&v,&w);
		u--,v--;
		edges[u].push_back({w,v});
	}
	vector < vector <ll> > dis(n,vector <ll> (k+1,1e8));
	vector <int> vis(n); 
	priority_queue <pii ,vector <pii >, greater< pii > > q;

	q.emplace(0ll,st);
	while(!q.empty()){
		v = q.top().second, w = q.top().first;
		q.pop();
		if(vis[v]>=k) continue;
		// for the varient, check if this path is greater than previous, if not, continue
		//if(vis[v]>0 && w == dis[v][vis[v]-1]) continue; 
		dis[v][vis[v]] = w; 
		vis[v]++;
		for(auto nd:edges[v]){
			q.emplace(w+nd.first,nd.second);
		}
	}
	ll ans = dis[des][k-1];
	if(ans==1e8) ans = -1;
	printf("%lld\n", ans);
}

int main()
{
	int t = 1,n,m; 
	scanf("%d%d", &n,&m);
	while(n||m){
		K_shortest(n,m);
		scanf("%d%d", &n,&m);
	}
	return MONKE;
}
