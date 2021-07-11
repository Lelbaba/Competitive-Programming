#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());

using namespace std;
using ll = long long;
const int MONKE = 0;

// 5472940991761 worst carmichael number

ll bigmul(ll num,ll pow,ll mod){
	ll ans = 0;
	for(;pow>0;pow>>=1){
		if(pow&1) ans = (ans+num) % mod;
		num = (num+num) % mod;
	}
	return ans;
}
ll bigmod(ll num,ll pow,ll mod){
	ll ans = 1;
	for(;pow>0;pow>>=1){
		if(pow&1) ans = bigmul(ans,num,mod);
		num = bigmul(num,num,mod);
	}
	return ans;
}

// handle bigmod overflow
vector <int> primes;
vector <bool> prime(200,true);
bool check_primality(ll p){
	if(p<2) return false;
	if(primes.empty()){
		for(int i=2;i<100;i++){
			for(int j=i+i;j<200;j+=i) prime[j] = false;
		}
		for(int i=2;i<200;i++){
			if(prime[i]) primes.push_back(i);
		}
	}
	for(auto a: primes){
		if(p!=a and bigmod(a,p-1,p) != 1) return false;
	}
	return true;
}
int main()
{
	ll n;
	while(cin>>n){
		if(check_primality(n)) cout<<n<<endl;
	}
	return MONKE;
}