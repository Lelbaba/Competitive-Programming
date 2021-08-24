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
using PLL = pair <LL,LL>;
// given a, b will find solutions for
// ax + by = 1
tuple <LL,LL,LL> EGCD(LL a, LL b){
    if(b == 0) return {1, 0, a};
    else{
        auto [x,y,g] = EGCD(b, a%b);
        return {y, x - a/b*y,g};
    }
}
// given modulo equations, will apply CRT
PLL CRT(vector <PLL> &v){
    PLL ans = {0,1};
    auto &[V, M] = ans;
    for(auto &[val,mod]:v){
        auto [x,y,g] = EGCD(M, mod);
        if((val-V)%g != 0)
            return {-1,0};
        ans = {V + x*(val-V)/g % (mod/g) * M, M*mod/g};
        V = (V%M + M)%M; //might be unnecessary
    }
    return ans;
}

mod
int main()
{
    monke_flip
    vector <crt_dt> v;
    v.emplace_back(3,7);
    v.emplace_back(1,3);
    auto x = CRT(v);
    dbg(x.val,x.mod);
    return MONKE;
}