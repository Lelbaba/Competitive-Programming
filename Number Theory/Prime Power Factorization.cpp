#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct factors
{
	ll prm;
	ll power;
};
const ll N=1000005;
bool is_prime[N+5];
vector <ll> primes;
ll smallest[N+5];

void seive(){
	memset(is_prime,true,sizeof is_prime);
    for(ll i=2;i<=N;i++){
        if(is_prime[i])
        	primes.push_back(i);
        for(auto p:primes){
            if(p*i>N)   break;
            is_prime[p*i] = false;
            smallest[i] = p;
            if(i%p==0)  break;
        }
    }
}

vector <factors> factorize(ll n){
	if(primes.empty()){
		seive();
	}
	vector <factors> ans;
	for(auto p:primes){
		if(p*p>n){
			break;
		}
		if(n%p==0){
			ll cnt = 0;
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
	auto v = factorize(882000);
	for(auto x:v) cout<<x.prm<<" "<<x.power<<endl;
	return 0;
}
