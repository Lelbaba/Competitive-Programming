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

vector <bool> prime;
vector <ll> primes;

void seive(ll n = 1<<20){
    prime.assign(n+1,true);
    
    for(ll i=2;i<=n;i++){
        if(prime[i]) 
            primes.push_back(i);

        for(auto p:primes){
            if(p*i>n or (i-1)%p == 0)   break;
            prime[p*i] = false;
        }
    }
}

vector <pair<ll,int>> factorize(ll n){
	if(primes.empty()) seive();
	int cnt = 0;
	vector <pair<ll,int>> ans;

	for(auto p:primes){
		if(p*p>n) break;
		for(cnt=0; n%p==0; cnt++,n/=p);
		if (cnt>0) ans.emplace_back(p,cnt);
	}

	if(n!=1) ans.emplace_back(n,1);
	return ans;
}


int main()
{
	auto b = factorize(72);
	for(auto x:b){
		cout<<x.first<<" "<<x.second<<endl;
	}
	return MONKE;
}