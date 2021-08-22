#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());

using namespace std;
using LL = long long;
const int MONKE = 0;
using ULL = unsigned long long;
// 5472940991761 worst carmichael number

inline ULL mul(ULL a,ULL b,ULL mod){
    LL ans = a * b - mod * (ULL) (1.L / mod * a * b);
    return ans + mod * (ans < 0) - mod * (ans >= (LL) mod);
}
inline ULL bigmod(ULL num,ULL pow,ULL mod){
    ULL ans = 1;
    for( ;  pow > 0;  pow >>= 1, num = mul(num, num, mod))
        if(pow&1) ans = mul(ans,num,mod);
    return ans;
}
inline bool is_prime(ULL n){
    if(n < 2 or n % 6 % 4 != 1) 
        return (n|1) == 3;
    ULL a[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    ULL s = __builtin_ctzll(n-1), d = n >> s;
    for(ULL x: a){
        ULL p = bigmod(x % n, d, n), i = s;
        for( ; p != 1 and p != n-1 and x % n and i--; p = mul(p, p, n));
        if(p != n-1 and i != s)
            return false;
    }
    return true;
}
// handle bigmod overflow
vector <int> primes;
vector <bool> prime(200,true);
bool check_primality(LL p){
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
	LL n;
	while(cin>>n){
		if(check_primality(n)) cout<<n<<endl;
	}
	return MONKE;
}