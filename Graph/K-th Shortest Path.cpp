#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair <long long,int>;

const int MONKE = 0;


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

	q.push({0ll,st});
	while(!q.empty()){
		v = q.top().second, w = q.top().first;
		q.pop();
		if(vis[v]>=k) continue;
		dis[v][vis[v]] = w;
		vis[v]++;
		for(auto nd:edges[v]){
			q.push({w+nd.first,nd.second});
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
