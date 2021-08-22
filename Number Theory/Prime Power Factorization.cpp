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

vector <bool> prime;
vector <LL> primes;

void seive(LL n = 1<<20){
    prime.assign(n+1,true);
    
    for(LL i=2;i<=n;i++){
        if(prime[i]) 
            primes.push_back(i);

        for(auto p:primes){
            if(p*i>n)   break;
            prime[p*i] = false;
            if(i%p == 0) break;
        }
    }
}

vector <pair<LL,int>> factorize(LL n){
	if(primes.empty()) seive();
	int cnt = 0;
	vector <pair<LL,int>> ans;

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