#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MONKE = 0;
const int maxn = 1e5+5;
//LOJ 1026
class articulation_graph
{
	public:
	vector <vector <int> > adj; //need to initialize
	int timer;
	vector <int> in,low;
	vector <bool> vis;
	set <int> cut_points;
	vector <pair <int,int> > bridges;
	void dfs(int node,int par=-1){
		vis[node] = true;
		in[node] = low[node] = timer++;
		int kids = 0;
		for(auto x:adj[node]){
			if(x==par) continue;	// handle for directed graphs/multi-edges
			if(vis[x]){
				low[node] = min(low[node],in[x]);
			}
			else{
				kids++;
				dfs(x,node);
				low[node] = min(low[node],low[x]);
				if(in[node]<=low[x] && par!=-1){
					cut_points.insert(node);
				}
				if(in[node]<low[x]){
					bridges.push_back({node,x});
				}
			}
		}
		if(par==-1 && kids>1){
			cut_points.insert(node);
		}
	}
	vector <int> get_cutpoints(int n){
		vector <int> ans;
		cut_points.clear();
		timer = 0;
		low.assign(n,0);
		in.assign(n,0);
		vis.assign(n,false);
		for(int i=0;i<n;i++){
			if(!vis[i]) dfs(i);
		}
		for(auto x:cut_points) ans.push_back(x);
		return ans;
	}
	vector <pair <int,int> > get_bridges(int n){
		bridges.clear();
		timer = 0;
		low.assign(n,0);
		in.assign(n,0);
		vis.assign(n,false);
		for(int i=0;i<n;i++){
			if(!vis[i]) dfs(i);
		}
		return bridges;
	}
};


void solve(){
    int n,u,v;
    cin>>n;
    vector < vector <int> > adj(n);
    string s;
    for(int i=0;i<n;i++){
    	cin>>u>>s;
    	s = s.substr(1,s.size()-2);
        int num = stoi(s);
        for(int j=0;j<num;j++){
            cin>>v;
            adj[u].push_back(v);
        }
    }
    articulation_graph G;
    G.adj = adj;
    auto bridges = G.get_bridges(n);
    cout<<bridges.size()<<" critical links\n";
    for(auto &x:bridges){
        if(x.first>x.second) swap(x.first,x.second);
    }
    sort(bridges.begin(), bridges.end());
    for(auto x:bridges){
        cout<<x.first<<" - "<<x.second<<endl;
    }
}

int main(){
	int t;
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cin>>t;
    for(int tc=1;tc<=t;tc++){
        cout<<"Case "<<tc<<":\n";
        solve();
    }
}