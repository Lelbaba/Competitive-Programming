#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using LL = long long;
const int MONKE = 0;

struct Weighted_Graph {
    int size = 0, cnt = 0;
    vector < vector <int> > Adj;
    vector < tuple <int, int, int>> Edges;
    Weighted_Graph(int size = 0) : size(size), Adj(size) {}
    void add_edge(int u, int v, int w){
        Edges.emplace_back(u, v, w);
        Adj[u].push_back(cnt);
        Adj[v].push_back(cnt++);
    }
    
};

int main(){
    monke_flip
    int n;
    cin >> n;
    return MONKE;
}


