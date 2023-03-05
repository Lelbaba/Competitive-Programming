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
// CF 706 D

class node{
    public:
        vector <int> route;
        int path = 0, leaf = 0;
    node(int n = 0){
        route.assign(n,-1);
    }
};
class TRIE{
    public:
        int ptr = 0,n;
        vector <node> Tree;
        node temp;
    TRIE(int _n){
        n = _n;
        Tree.emplace_back(n);
    }
    void insert(vector <int> &seq){
        int cur = 0;
        Tree[0].path++;
        for(auto x:seq){
            int& erpor = Tree[cur].route[x];
            if(erpor == -1){
                Tree.emplace_back(n);
                erpor = ++ptr;
            }
            cur = erpor;
            Tree[cur].path++;
        }
        Tree[cur].leaf++;
    }
    void erase(vector <int> &seq){
        int cur = 0;
        Tree[0].path--;
        for(auto x:seq){
            assert(Tree[cur].path >= 0);
            cur = Tree[cur].route[x];
            Tree[cur].path--;
        }
        Tree[cur].leaf--;
    }
    bool find(vector <int> &seq){
        int cur = 0;
        for(auto x:seq){
            cur = Tree[cur].route[x];
            if(cur < 0 or Tree[cur].path == 0) 
                return false;
        }
        return Tree[cur].leaf > 0;
    }
    int max_xor(vector <int> &seq){
        int cur = 0, val = 0;
        for(auto x:seq){
            val <<= 1;
            int bad = Tree[cur].route[x], good = Tree[cur].route[x^1];
            if(good >=0 and Tree[good].path>0){
                val+= (x^1);
                cur = good;
            } else {
                val+= x;
                cur = bad;
            } 
        }
        return val;
    }
};

int main()
{
    monke_flip
    TRIE T(2);
    vector <int> v(32);
    T.insert(v);
    int n,x;
    char ch;
    cin >>n;
    for(int i=0;i<n;i++){
        cin >>ch >>x;
        for(int i=31;i>=0;i--){
            v[31-i] = (x&(1<<i)) ? 1:0;
        } 
        if(ch == '+') T.insert(v);
        else if(ch == '-') T.erase(v);
        else{
            int val = T.max_xor(v);
            cout<<(x^val)<<'\n';
        }
    }
    return MONKE;
}