#include <bits/stdc++.h>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#ifdef LEL
#include "dbg.h"
#else
#define dbg(...) {/* temon kichu na; */}
#endif
using namespace std;
using LL = long long;
const int MONKE = 0;

//untested 

class top_sort{
public:
	vector <vector <int> > adj;
	vector <int> in,order;
	int n;
	top_sort(int _n,vector <pair<int,int> > &edges){
		n = _n;
		adj.clear();
		adj.resize(n);
		in.resize(n);
		for(auto &e:edges){
			adj[e.first].push_back(e.second);
			in[e.second]++;
		}
	}
	void make_sorted(){
		queue <int> q;
		order.clear();
		for(int i=0;i<n;i++){
			if(!in[i]) q.push(i);
		}
		while(!q.empty()){
			auto t = q.front();
			order.push_back(t);
			q.pop();
			for(auto v:adj[t]){
				in[v]--;
				dbg(v);
				if(!in[v]){
					q.push(v);
				}
			}
		}
	}
};

int main()
{
	int t;
	fastio
	cin>>t;
	for(int tc=1;tc<=t;tc++){
		int n,m;
		cin>>n>>m;
		vector <vector <int> >adj(n);
		vector <pair<int,int> >edges(m);
		for(auto &e:edges){
			cin>>e.first>>e.second;
			e.first--; e.second--;
		}
		top_sort graph(n,edges);
		graph.make_sorted();
		for(auto x:graph.order){
			cout<<x+1<<" ";
		}
	}
	return MONKE;
}