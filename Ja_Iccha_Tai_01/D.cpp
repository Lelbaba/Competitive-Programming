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

int main()
{
	monke_flip
	ll n, m, t;
	cin >>n >>m >>t;
	vector <vector<edge> > adj(n);

	for(int i=0; i<m; i++){
		ll u, v, w;
		cin >>u >>v >>w;
		adj[u-1].emplace_back(w,v-1);
	}
	vector <vector <ll>> DP(n, vector<ll> (2,LLONG_MAX) );
	vector <vector <int>> PATH(n, vector<int> (m+1) );

	DP[0][0] = 0;
	
	ll ans = -1;
	
	for(ll len = 0;len <=m;len++){
		for(int i=0;i<n;i++)
			DP[i][len+1&1] = LLONG_MAX;
		if(DP[n-1][len&1]<=t) 
			ans = len+1;

		for(int i=0;i<n;i++){

			if(DP[i][len&1] == LLONG_MAX) continue;
			
			for(auto x:adj[i]){
				if(DP[i][len&1]+x.first < DP[x.second][len+1&1]){
					DP[x.second][len+1&1] = DP[i][len&1] + x.first;
					PATH[x.second][len+1] = i;
				}
			}
		}
	}
	cout<<ans<<'\n';
	vector <ll> path;
    for(int i=ans, j = n-1; i>0; j = PATH[j][--i]){
        path.push_back(j+1);
    }
    reverse(path.begin(), path.end());
    for(auto x:path) cout<<x<<" ";
	return MONKE;
}