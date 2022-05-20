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
ULL bigmod(ULL num,ULL pow,ULL mod){
    num = num%mod;
    ULL ans = 1;
    for(;pow>0;pow>>=1){
        if(pow&1) ans = ans*num % mod;
        num = num*num % mod;
    }
    return ans;
}
const LL P = 1e9 + 7, p = 97, sh = 30;
/*....................................................................*/ 
LL get(string &s){
    LL ans = 0;
    for(LL i = 0, x = 1; i < s.size(); i++, x = x * p % P){
        ans += (s[i] - sh) * x;
        ans %= P;
    }
    return ans;
}
int main()
{
    monke_flip
    string K, E;
    LL shift;
    cin >> K >> E >> shift;
    LL k = get(K), e = get(E);
    LL x = bigmod(k, e, P);
    vector <int> v(sh + 1);
    v[0] = x % p;
    for(int i = 1; i <= sh; i++){
        v[i] = (v[i - 1] * v[i - 1] + shift + i) % p;
        if(v[i] == 1)
            v[i - 1] = 0;
        shift = shift * (x + 2) % p;
    }
    string s;
    for(auto &e: v){
        if(e > 1)
            s += (e + sh) ;
    }
    cout << s;
    return MONKE;
}