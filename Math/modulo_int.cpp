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


ll inv_mod(ll a, ll m){
    ll _m = m, q, t, x, y;
    if (m == 1)
        return 0;
 
    for (y = 0, x = 1;   a > 1;  t = y, y = x-q*y, x = t) {
        q = a / m,   t = m;
        m = a % m,   a = t;
    }
    return x < 0 ? x + _m : x;
}
class modulo_int{
    public:
        ll val;
        static const ll mod = 1e9+7; // don't use if it isn't a prime, careful of overflow

    modulo_int(ll _val = 0){
        val = _val > 0 ? _val%mod : _val%mod + mod;
    }

    modulo_int operator + (modulo_int rhs){ return modulo_int((val + rhs.val)); }
    modulo_int operator - (modulo_int rhs){ return modulo_int((val - rhs.val)); }
    modulo_int operator * (modulo_int rhs){ return modulo_int((val * rhs.val)); }
    modulo_int operator / (modulo_int rhs){ return modulo_int( binpow(rhs, mod-2) * val);}

    void operator += (modulo_int rhs){ *this = *this + rhs; }
    void operator -= (modulo_int rhs){ *this = *this - rhs; }
    void operator *= (modulo_int rhs){ *this = *this * rhs; }
    void operator /= (modulo_int rhs){ *this = *this / rhs; }

    friend modulo_int binpow (modulo_int val, ll p){
        modulo_int ans = 1;
        for(;p>0; p>>=1){
            if(p&1) ans = ans*val;
            val *= val;
        }
        return ans;
    }
    friend ostream& operator << (ostream& o, modulo_int &a){
        o << a.val;
        return o;
    }
    friend istream& operator >> (istream& o, modulo_int &a){
        o >> a.val;
        return o;
    }
};
int main()
{
    monke_flip
    
    return MONKE;
}