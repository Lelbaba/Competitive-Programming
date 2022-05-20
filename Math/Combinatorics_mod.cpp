#include <bits/stdc++.h>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#ifdef LEL
#include "dbg.h"
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using LL = long long;
const int MONKE = 0;

const int N = 2e5+5;
const int mod = 1e9+7;

namespace com{
    array <int, N+1> fact, inv, inv_fact;
    void init(){
        fact[0] = inv_fact[0] = 1;
        for(int i = 1; i <= N; i++){
            inv[i] = i == 1 ? 1 : (LL) inv[i - mod%i] * (mod/i + 1) % mod;
            fact[i] = (LL) fact[i-1] * i % mod;
            inv_fact[i] = (LL) inv_fact[i-1] * inv[i] % mod;
        }
    }
    int C(int n,int r){
        if(fact[0] != 1) init();
        return (r < 0 or r > n) ? 0 : (LL) fact[n]*inv_fact[r] % mod * inv_fact[n-r] % mod;
    }
}
int main()
{
	int t;
	cin>>t;
	for(int tc = 1; tc<=t; tc++){
		int n,k;
		cin>>n>>k;
		printf("Case %d: %d\n",tc,com::C(n,k) );
	}
	return MONKE;
}