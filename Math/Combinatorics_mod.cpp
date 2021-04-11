#include <bits/stdc++.h>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#ifdef LEL
#include "dbg.h"
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using ll = long long;
const int MONKE = 0;

ll inv_mod(ll a, ll m){
    ll _m = m;
    ll y = 0, x = 1;
 
    if (m == 1)
        return 0;
 
    while (a > 1) {
        ll q = a / m, t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += _m;
    return x;
}
class combi
{
public:
	ll mod;
	vector <ll> factorial,inv;
	void init(ll n,ll m = ll(1e9+7)){
		mod = m;
		inv.reserve(n+1);
		factorial.reserve(n+1);
		factorial[0] = 1;
		inv[0] = inv_mod(1,mod);
		for(int i=1;i<=n;i++){
			factorial[i] = (factorial[i-1]*i)%mod;
			inv[i] = inv_mod(factorial[i],mod);
		}
	}
	ll C(ll n,ll r){
		if(r>n) return 0;
		ll ans = 1;
		ans = ans*factorial[n]%mod;
		ans = ans*inv[r]%mod;
		ans = ans*inv[n-r]%mod;
		return ans;
	}
} com;

int main()
{
	com.init(1000003,1000003);
	int t;
	cin>>t;
	for(int tc = 1; tc<=t; tc++){
		ll n,k;
		cin>>n>>k;
		printf("Case %d: %lld\n",tc,com.C(n,k) );
	}
	return MONKE;
}