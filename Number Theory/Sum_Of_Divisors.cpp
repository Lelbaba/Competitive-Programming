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
//CF 1512 G

vector <bool> prime;
vector <ll> primes,SOD,SPF_pow;

void seive(ll n = 1<<20){
    prime.assign(n+1,true),SPF_pow.assign(n+1,1);
    SOD.resize(n+1);
    SOD[1] = 1;

    for(ll i=2;i<=n;i++){
        if(prime[i]) {
        	SOD[i] = i+1, SPF_pow[i] = i;
            primes.push_back(i);
        }
        for(auto p:primes){
            if(p*i>n)   break;
            prime[p*i] = false;
            if(i%p == 0){
            	SPF_pow[p*i] = p*SPF_pow[i];
            	SOD[p*i] = SOD[i]/SOD[SPF_pow[i]] * (SOD[SPF_pow[i]] + SPF_pow[p*i]);
            	break;
            } else {
            	SOD[p*i] = SOD[i]*SOD[p];
            	SPF_pow[p*i] = p;
            }
        }
    }
}

int main()
{
	monke_flip
	int n = 1e7+5,t;
	seive(n);
	vector <int> ans(n,-1);
	for(int i=1;i<n;i++){
		if(SOD[i]<n and ans[SOD[i]] == -1) ans[SOD[i]] = i;
	}
	cin>>t;
	while(t--){
		cin>>n;
		cout<<ans[n]<<'\n';
	}
	return MONKE;
}