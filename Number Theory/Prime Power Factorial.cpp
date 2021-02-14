#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct P
{
	ll prm;
	ll power;
};
const ll N=1000005;
bool is_prime[N+5];
vector <ll> primes;
ll divv[N+5];

void seive()
{
    ll i,j;
    fill(is_prime+2,is_prime+N+1,true);

    for(i=2;i<=N;i++)
    {
        if(is_prime[i])     primes.push_back(i);
        for(auto x:primes)
        {
            if(x*i>N)   break;
            is_prime[x*i]= false;
            divv[i]=x;
            if(i%x==0)  break;
        }
    }
}

vector <P> factorize(ll n){
	if(primes.empty()){
		seive();
	}
	vector <P> ans;
	for(auto x:primes){
		if(x*x>n){
			break;
		}
		if(n%x==0){
			ll cnt = 0;
			while(n%x==0){
				cnt++;
				n/=x;
			}
			ans.push_back({x,cnt});
		}
	}
	if(n!=1){
		ans.push_back({n,1});
	}
	return ans;
}


int main()
{
	vector <P> myans;
	myans = factorize(24ll);
	cout<<primes.size()<<endl;
	for(auto x:myans){
		printf("%lld %lld\n",x.prm,x.power);
	}
	myans = factorize(ll(1e9+7));
	for(auto x:myans){
		printf("%lld %lld\n",x.prm,x.power);
	}
	return 0;
}
