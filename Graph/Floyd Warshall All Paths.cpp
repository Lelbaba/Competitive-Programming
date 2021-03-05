#include <bits/stdc++.h>
using namespace std;
using ll =  long long;
const int MONKE = 0;
ll path[35][35];
int input(int n){
	int u,v;
	memset(path,0, sizeof path);

	int Max = -1;
	for(int i=0;i<n;i++){
		scanf("%d%d", &u,&v);
		Max = max(Max,max(u,v));
		path[u][v] = 1;
	}
	return Max;
}
void floyd_warshall_all_paths(int Max){
	for(int k=0;k<=Max;k++){
		for(int i=0;i<=Max;i++) for(int j=0;j<=Max;j++)
			if(path[i][k]&&path[k][j]) 
				path[i][j]+= path[i][k]*path[k][j];
	}
	
	for(int k=0;k<=Max;k++) if(path[k][k]){
		for(int i=0;i<=Max;i++) for(int j=0;j<=Max;j++)
			if(path[i][k]&&path[k][j])
				path[i][j] = -1;
	}
		
}
void solve(int n){
	int Max = input(n);
	floyd_warshall_all_paths(Max);
	for(int i=0;i<=Max;i++){
		for(int j=0;j<Max;j++){
			printf("%lld ",path[i][j]);
		}
		printf("%lld\n", path[i][Max]);
	}

}
int main()
{
	int T=0,n;
	while(scanf("%d", &n)!=EOF){
		printf("matrix for city %d\n", T++);
		solve(n);
	}
	return MONKE;
}
