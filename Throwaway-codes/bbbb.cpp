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
namespace rho{
    inline ULL mul(ULL a,ULL b,ULL mod){
        LL ans = a * b - mod * (ULL) (1.L / mod * a * b);
        return ans + mod * (ans < 0) - mod * (ans >= (LL) mod);
    }
    inline ULL bigmod(ULL num,ULL pow,ULL mod){
        ULL ans = 1;
        for( ;  pow > 0;  pow >>= 1, num = mul(num, num, mod))
            if(pow&1) ans = mul(ans,num,mod);
        return ans;
    }
    inline bool is_prime(ULL n){
        if(n < 2 or n % 6 % 4 != 1) 
            return (n|1) == 3;
        ULL a[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        ULL s = __builtin_ctzll(n-1), d = n >> s;
        for(ULL x: a){
            ULL p = bigmod(x % n, d, n), i = s;
            for( ; p != 1 and p != n-1 and x % n and i--; p = mul(p, p, n));
            if(p != n-1 and i != s)
                return false;
        }
        return true;
    }
    ULL get_factor(ULL n) {
        auto f = [&](LL x)  { return mul(x, x, n) + 1; };
        ULL x = 0, y = 0, t = 0, prod = 2, i = 2, q;
        for(  ; t++ %40 or gcd(prod, n) == 1;   x = f(x), y = f(f(y)) ){
            (x == y) ? x = i++, y = f(x) : 0;
            prod = (q = mul(prod, max(x,y) - min(x,y), n)) ? q : prod;
        }
        return gcd(prod, n);
    }
    map <ULL, int> factorize(ULL n){
        map <ULL, int> res;
        if(n < 2)   return res;
        ULL small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
        for (ULL p: small_primes)
            for( ; n % p == 0; n /= p, res[p]++);

        auto _factor = [&](ULL n, auto &_factor) {
            if(n == 1)   return;
            if(is_prime(n)) 
                res[n]++;
            else {
                ULL x = get_factor(n);
                _factor(x, _factor);
                _factor(n / x, _factor);
            }
        };
        _factor(n, _factor);
        return res;
    }
}

/*....................................................................*/ 
using LLL = __int128;
int koto(LLL a, LLL b, LLL v) {
    int ans;
    LLL x = 1;
    for(ans = 0; x <= b; ans++, x = x * v) {
        if(b / x == (a - 1) / x) break;
    }
    return ans - 1;
}
void solve() {
    LL a, b, c;
    cin >> a >> b >> c;
    auto F = rho :: factorize(c);
    int x = 1e9;
    for(auto [e, cnt]: F){
        int z = koto(a, b, e);
        x = min(x, z / cnt);
    }
    cout << x << '\n';
}

int main()
{
    monke_flip
    int t = 1; 
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        solve();
    }
    return MONKE;
}