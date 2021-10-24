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
class node{
public:
    int s, e, m, state;
    LL val, lazy;
    unique_ptr <node> L, R;
    const LL I = 0;
    node(int S,int E){
        s = S, e = E, m = S+E >> 1;
        val = lazy = I;
        if(s != e){
            L = make_unique <node> (s, m);
            R = make_unique <node> (m+1, e);
        }
    }
    void apply(LL U){
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
    LL get(LL a, LL b, int l = 0,int r = 0){
        return a+b;
    }
    void update(int S,int E, LL U){
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
    LL query(int S,int E){
        propogate();
        if(S>E)
            return I;
        if(s == S and e == E)
            return val;
        return get(L-> query(S,min(m,E)), R-> query(max(S,m+1), E));
    }
};
/*....................................................................*/ 

void solve(){
    int n, q;
    cin >> n >> q;
    node T(0, n-1);
    while(q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if(t){
            cout << T.query(l, r) << '\n';
        } else {
            LL val;
            cin >> val;
            T.update(l, r, val); 
        }
    }

}

int main()
{
    monke_flip
    int t = 1; 
    cin>>t;
    for(int tc=1; tc <= t; tc++){
        cout << "Case " << tc << ":\n";
        solve();
    }
    return MONKE;
}