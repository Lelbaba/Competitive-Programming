
vector <int> out[35];
int color[35];

void dfs(int node,int par){
	color[node] = 1;
	for(auto v:out[node]){
		if(color[v]==1){
			//cycle
		}
		if(color[v]==0) dfs(v,node);
	}
	color[node] = 2;
}

void detect_loop(int n){
	memset(color,0,sizeof color);
	for(int i=0;i<n;i++){
		if(color[i]==0){
			dfs(i,-1);
		}
	}
}
