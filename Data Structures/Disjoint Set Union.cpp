// CF 278C
#include <bits/stdc++.h>
using namespace std;
#define MONKE 0
using LL = long long;
using ld = long double;

int par[100005];


class DSU{
    public:
        vector <int> par,size;
        // parent of each set and size of each set
    DSU(int n){
        for(int i=0;i<n;i++){
            par.push_back(i);
            size.push_back(1);
        }
    }
    // ancestor
    int Anc(int node){
        if(par[node] == node) 
            return node;
        return par[node] = Anc(par[node]); 
    }
    bool same(int x,int y){
        return Anc(x) == Anc(y);
    }
    void Union(int x,int y){
        x = Anc(x),y = Anc(y);
        size[x] += size[y];
        par[y] = x;
    }
    int Size(int node){
        return size[Anc(node)];
    }
};

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
