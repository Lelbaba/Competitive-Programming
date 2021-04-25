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
class djikstra{
public:
    ll n = -1;
    vector <vector <edge> > adj;
    vector <ll> D;
    vector <vector <ll> > path;
    djikstra(vector < vector <edge> > &A){
        n = A.size();
        adj = A;
        D.assign(n,LLONG_MAX);
        path.resize(n);
    }
    void find_shortest_paths(ll s) {
        priority_queue < edge, vector <edge>, greater<edge> > Q;
        Q.emplace(0,s);
        while(!Q.empty()){

            ll node = Q.top().second, d = Q.top().first;
            Q.pop();
            if(d>D[node]) continue;
            D[node] = d; 
            for(auto e:adj[node]){
                ll _next = e.second, dis = e.first;
                if(D[_next]>dis+d){
                    D[_next] = dis+d;
                    Q.emplace(dis+d,_next);
                }
            }
        }
        Q.emplace(0,s);
        while(!Q.empty()){

            ll node = Q.top().second, d = Q.top().first;
            Q.pop();
            if(d>D[node]) continue;
            D[node] = d; 
            for(auto e:adj[node]){
                ll _next = e.second, dis = e.first;
                if(D[_next] == dis+d){
                    path[_next].push_back(node);
                    Q.emplace(dis+d,_next);
                }
            }
        }
    }

};

void solve(){
    int n,m;
    cin>>n>>m;
    vector <vector<edge>> adj(n);
    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        adj[u].emplace_back(w,v);
        adj[v].emplace_back(w,u);
    }
    // use djikstra to precalculate what is the previous nodes that lead to shortest path
    djikstra D(adj);
    D.find_shortest_paths(0);
    // dominator tree
    // LCA
}

int main()
{
    monke_flip
    int t = 1; 
    cin>>t;
    for(int tc=1; tc<=t; tc++){
        solve();
    }
    return MONKE;
}