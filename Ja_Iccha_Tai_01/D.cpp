#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using ll = long long;
const int MONKE = 0;
using edge = pair <ll,ll>;
struct dt
{
	ll first,second,cnt;
	bool operator < (dt &rhs){
		return first <rhs.first or (first == rhs.first and (second<rhs.second));
	}
};
class djikstra{
public:
	ll n = -1;
	vector <vector <edge> > adj;
	vector <ll> D,path;
	djikstra(vector < vector <edge> > &A){
		n = A.size();
		adj = A;
		D.assign(n,LLONG_MIN);
		path.assign(n,-1);
	}
	ll find_shortest_paths(ll s,ll f,ll t) {
		priority_queue < edge, vector <edge>, greater<edge> > Q;
		Q.emplace(0,s,1);
		ll ans = 0;
		while(!Q.empty()){

			ll node = Q.top().second, d = Q.top().first, cnt = Q.top.cnt();
			Q.pop();
			if(d>t) continue;
			for(auto e:adj[node]){
				ll _next = e.second, dis = e.first;
				if(dis+d<=t){
					if(e.cnt>D[_next]){
						D[_next] = e.cnt;
						path[_next] = node;
					}
					Q.emplace(dis+d,_next);
				}
			}
		}
	}

};


int main()
{
	monke_flip
	ll n, m, t;
	cin >>n >>m >>t;
	adj.resize(n);

	for(int i=0; i<m; i++){
		ll u, v, w;
		cin >>u >>v >>w;
		adj[u-1].emplace_back(w,v-1);
	}
	djikstra G(adj);
	G.find_shortest_paths(n-1);
	auto D = G.D;
	path.assign(n,-1);

	ll ans = dfs(0,n-1,t);
	cout<<ans<<'\n';
	for(ll i=0,node = 0;i<ans;i++, node = path[node]){
		cout<<node+1<<" ";
	}
	return MONKE;
}