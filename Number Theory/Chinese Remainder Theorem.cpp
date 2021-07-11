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
class gcd_dt{
    public:
        ll x,y,g;
    gcd_dt(ll _x,ll _y,ll _g){
        x = _x, y = _y, g = _g;
    }
};
gcd_dt egcd(ll a,ll b){
    if(b==0){
        return gcd_dt(1,0,a);
    }
    auto tem = egcd(b,a%b);
    return gcd_dt(tem.y, tem.x - a/b*tem.y, tem.g);
}
class crt_dt{
    public:
        ll val, mod;
    crt_dt(ll _val = 0,ll _mod = 1){
        mod = _mod;
        val = _val%mod;
        val = (val+mod)%mod;
    }
};
crt_dt CRT(vector <crt_dt> &v){
    crt_dt ans;
    for(auto &e:v){
        auto tem = egcd(ans.mod,e.mod);
        if((e.val-ans.val)%tem.g != 0)
            return crt_dt(-1,0);
        ans = crt_dt(ans.val + tem.x*(e.val-ans.val)/tem.g % (e.mod/tem.g) * ans.mod, ans.mod*e.mod/tem.g);
    }
    return ans;
}

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