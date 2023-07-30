#include <bits/stdc++.h>
using namespace std;
using LL = long long;

/*....................................................................*/ 

/*....................................................................*/ 
struct DSU {
    vector <int> par, size;
    DSU(int n) : par(n), size(n) {
        fill(size.begin(), size.end(), 1);
        iota(par.begin(), par.end(), 0);
    }
    int root(int node){
        if(par[node] == node) return node;
        return par[node] = root(par[node]); 
    }
    bool same(int x, int y){
        return root(x) == root(y);
    }
    void merge(int x, int y){
        x = root(x), y = root(y);
        if(x == y) return;
        if(size[x] < size[y]) swap(x, y);
        size[x] += size[y], par[y] = x;
    }
};
int main() {
    cin.tie(0) -> sync_with_stdio(0);
}
