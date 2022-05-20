#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke chrono::system_clock::now().time_since_epoch().count()
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using LL = long long;
using ULL = unsigned long long;
mt19937_64 rng(random_monke);
const int MONKE = 0;

/*....................................................................*/ 
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
/*....................................................................*/ 

int main()
{
	monke_flip
	
	return MONKE;
}