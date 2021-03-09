// CF 278C
#include <bits/stdc++.h>
using namespace std;
#define MONKE 0
using ll = long long;
using ld = long double;

int par[100005];

int root(int i){
	if(par[i]==i) return i;
	return par[i] = root(par[i]);
}

void dsu(int i,int j){
	par[root(j)] = root(i);
}

int main()
{
	int n,m,k;
	scanf("%d%d", &n,&m);
	for(int i=1;i<=m;i++) par[i] = i;
	set <int> languages;
	int zeroes = 0;
	for(int i=0;i<n;i++){
		scanf("%d", &k);
		if(k==0){
			zeroes++;
			continue;
		}
		vector <int> temp(k);
		for(auto &e:temp){ 
			scanf("%d", &e);
			languages.insert(e);
		}
		if(k>1){
			for(int j=1;j<k;j++){
				dsu(temp[0],temp[j]);
			}
		}

	}
	set <int> parts;
	for(auto i:languages){
		parts.insert(root(i));
	}
	printf("%d", zeroes+max(0,int(parts.size()-1)));
	return MONKE;
}
