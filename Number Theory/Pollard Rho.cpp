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
using ull = unsigned long long;
namespace rho{
    inline ull mul(ull a,ull b,ull mod){
        ll ans = a * b - mod * (ull) (1.L / mod * a * b);
        return ans + mod * (ans < 0) - mod * (ans >= (ll) mod);
    }
    inline ull bigmod(ull num,ull pow,ull mod){
        ull ans = 1;
        for( ;  pow > 0;  pow >>= 1, num = mul(num, num, mod))
            if(pow&1) ans = mul(ans,num,mod);
        return ans;
    }
    inline bool is_prime(ull n){
        if(n < 2 or n % 6 % 4 != 1) 
            return (n|1) == 3;
        ull a[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        ull s = __builtin_ctzll(n-1), d = n >> s;
        for(ull x: a){
            ull p = bigmod(x % n, d, n), i = s;
            for( ; p != 1 and p != n-1 and x % n and i--; p = mul(p, p, n));
            if(p != n-1 and i != s)
                return false;
        }
        return true;
    }
    ull get_factor(ull n) {
        auto f = [&](ll x)  { return mul(x, x, n) + 1; };
        ull x = 0, y = 0, t = 0, prod = 2, i = 2, q;
        for(  ; t++ %40 or gcd(prod, n) == 1;   x = f(x), y = f(f(y)) ){
            (x == y) ? x = i++, y = f(x) : 0;
            prod = (q = mul(prod, max(x,y) - min(x,y), n)) ? q : prod;
        }
        return gcd(prod, n);
    }
    map <ull, int> factorize(ull n){
        map <ull, int> res;
        if(n < 2)   return res;
        ull small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
        for (ull p: small_primes)
            for( ; n % p == 0; n /= p, res[p]++);

        auto _factor = [&](ull n, auto &_factor) {
            if(n == 1)   return;
            if(is_prime(n)) 
                res[n]++;
            else {
                ull x = get_factor(n);
                _factor(x, _factor);
                _factor(n / x, _factor);
            }
        };
        _factor(n, _factor);
        return res;
    }
}