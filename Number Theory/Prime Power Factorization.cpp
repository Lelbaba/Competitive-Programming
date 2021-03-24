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
vector <ll> primes,smallest;

void seive(ll n = ll(1e6)){
	prime.assign(n+1,true);
	smallest.assign(n+1,0);
    for(ll i=2;i<=n;i++){
        if(prime[i]){
        	smallest[i] = i;
        	primes.push_back(i);
        }
        for(auto p:primes){
            if(p*i>n)   break;
            prime[p*i] = false;
            smallest[p*i] = p;
            if(i%p==0)  break;
        }
    }
}

vector <pair <ll,int> > factorize(ll n){
	if(primes.empty()){
		seive();
	}
	vector <pair<ll,int> > ans;
	for(auto p:primes){
		if(p*p>n){
			break;
		}
		if(n%p==0){
			int cnt = 0;
			while(n%p==0){
				cnt++, n/=p;
			}
			ans.push_back({p,cnt});
		}
	}
	if(n!=1){
		ans.push_back({n,1});
	}
	return ans;
}


int main()
{
	auto b = factorize(65536);
	for(auto x:b){
		cout<<x.first<<" "<<x.second<<endl;
	}
	return MONKE;
}