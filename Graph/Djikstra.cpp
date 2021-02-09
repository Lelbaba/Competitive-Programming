#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 100005;
struct edge{
	int v;
	ll w;
	bool operator < (const edge &rhs) const{
		return w > rhs.w;
	}
};
struct graph{
	ll inf = (1LL<<61);
	int n;
	vector <edge> V[maxn];


	ll D[maxn];
	int path[maxn];
	ll djikstra(int s,int f) {
		int i,u,v;
		ll d,w;
		priority_queue <edge> Q;
		for(i=0;i<n;i++){
			D[i]=inf;
		}
		D[s] = 0;
		path[f] = path[s] = -1;
		Q.push({s,0});
		while(!Q.empty()){
			u = Q.top().v;
			d = Q.top().w;
			if(u==f) return d;
			Q.pop();
			for(auto X:V[u]){
				v = X.v;
				w = X.w;
				if(D[v]>d+w){
					D[v] = d+w;
					path[v] = u;
					Q.push({v,D[v]});
				}
			}
		}
		return D[f];
	}
	vector <ll> djikstra(int s) {
		int i,u,v;
		ll d,w;
		priority_queue <edge> Q;
		for(i=0;i<n;i++){
			D[i]=inf;
		}
		D[s] = 0;
		Q.push({s,0});
		while(!Q.empty()){
			u = Q.top().v;
			d = Q.top().w;
			Q.pop();
			for(auto X:V[u]){
				v = X.v;
				w = X.w;
				if(D[v]>d+w){
					D[v] = d+w;
					Q.push({v,D[v]});
				}
			}
		}
		vector <ll> ans;
		for(i=0;i<n;i++){
			ans.push_back(D[i]);
		}
		return ans;
	}

}g1;

int main()
{
	int e,i,j,k,n,m,u,v,t,a,b,c,r;
	ll w;
	cin>>n>>m;
	g1.n = n;
	for(i=0;i<m;i++){
		cin>>u>>v>>w;
		u--;v--;
		g1.V[u].push_back({v,w});
		g1.V[v].push_back({u,w});
	}
	g1.djikstra(0,n-1);
	r = n-1;
	if(g1.path[r]==-1)	cout<<-1;
	else{
		deque <int> ans;
		while(r>=0){
			ans.push_front(r+1);
			r = g1.path[r];
		}
		for(auto x:ans)	cout<<x<<" ";
	}
	return 0;
}
