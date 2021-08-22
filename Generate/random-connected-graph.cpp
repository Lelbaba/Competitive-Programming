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

/*....................................................................*/ 
vector <pair <int,int> > tree_generate (int n){
    vector <int> v = {0};
    vector <int> remaining;
    for(int i = 1; i < n; i++)
        remaining.push_back(i);
    shuffle(remaining.begin(), remaining.end(), rng);
    vector <pair <int,int>> ans;
    int idx = 0;
    for(auto e: remaining){
        uniform_int_distribution <int> gen(0, idx++);
        ans.emplace_back(e, v[gen(rng)]);
        v.push_back(e);
    }
    return ans;
}
vector <pair <int,int>> connected_graph_generate(int n, int m){
    auto ans = tree_generate(n);
    assert (m+n-1 <= n*(n-1)/2);
    map <int, set <int>> M;
    for(auto &[l,r]:ans){
        M[l].insert(r);
        M[r].insert(l);
    }
    for(int i = 0; i < n; i++)
        M[i].insert(i);
    uniform_int_distribution <int> gen(0,n-1);
    for(int i = 0; i < m; i++){
        for(int x, y; ;){
            x = gen(rng), y = gen(rng);
            if(M[x].find(y) == M[x].end()) {
                ans.emplace_back(x,y);
                M[x].insert(y), M[y].insert(x);
                break;
            }
        }
    }
    return ans;
}
int main()
{
    monke_flip
    cout << 100 << '\n';
    uniform_int_distribution <int> gen(4, 15);
    for(int i = 0; i < 100; i++){
        int n = gen(rng);
        uniform_int_distribution <int> xd(0, n-1);
        int m = xd(rng);
        cout << n << ' ' << m+n-1 << "\n\n";
        for(auto [l,r]:connected_graph_generate(n,m))
            cout << l << ' ' << r << '\n';
        cout << "\n";
    }
    return MONKE;
}