#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using ll = long long;
const int MONKE = 0;

template <typename DT> class node{
public:
    int s, e, m, state;
    DT val, lazy;
    node <DT> *L, *R;
    const DT I = 0;
    node(int S,int E){
        s = S, e = E, m = S+E >> 1;
        val = lazy = I;
        if(s != e){
            L = new node(s,m);
            R = new node(m+1,e);
        }
    }
    void apply(DT U){
        val += U*(e-s+1);
        lazy += U;
    }
    void reset(){
        lazy = I;
    }
    void propogate(){

        if(s == e)
            return;
        L-> apply(lazy);
        R-> apply(lazy);
        reset();
    }
    DT get(DT a, DT b, int l = 0,int r = 0){
        return a+b;
    }
    void update(int S,int E, DT U){
        propogate();
        if(S>E)
            return;
        if(S == s and E == e){
            apply(U);
            return;
        }
        L -> update(S , min(m,E), U);
        R -> update(max(S,m+1), E, U);
        val = get(L->val, R->val);
    }
    DT query(int S,int E){
        propogate();
        if(S>E)
            return I;
        if(s == S and e == E)
            return val;
        return get(L-> query(S,min(m,E)), R-> query(max(S,m+1), E));
    }
};
int main()
{
    monke_flip

    return MONKE;
}