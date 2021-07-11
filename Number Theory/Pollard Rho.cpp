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

ll mult(ll num,ll pow,ll mod){
    ll ans = 0;
    for(;pow>0;pow>>=1){
        if(pow&1) ans = (ans+num) % mod;
        num = (num+num) % mod;
    }
    return ans;
}
ll f(ll x, ll c, ll mod) {
    return (mult(x, x, mod) + c) % mod;
}

ll rho(ll n, ll _x = 2, ll c=1) {
    ll x = _x, y = _x, g = 1;
    while (g == 1) {
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = __gcd(abs(x - y), n);
    }
    return g;
}
ll brent(ll n, ll x0=2, ll c=1) {
    ll x = x0,g, q = 1, xs, y;
    int m = 128, l = 1;
    
    for(g = 1 ;g == 1; l<<=1) {
        y = x;
        for (int i = 1; i < l; i++)
            x = f(x, c, n);
        for(int k= 0;k < l && g == 1; k+= m, g = gcd(q,n)) {
            xs = x;
            for (int i = 0; i < m && i < l - k; i++) {
                x = f(x, c, n);
                q = mult(q, abs(y - x), n);
            }
        }
    }
    if (g == n) {
        do {
            xs = f(xs, c, n);
            g = gcd(abs(xs - y), n);
        } while (g == 1);
    }
    return g;
}
int main()
{
    monke_flip
    cout<<brent(65536);
    return MONKE;
}