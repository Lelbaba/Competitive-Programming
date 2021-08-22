#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using LL = long long;
const int MONKE = 0;


vector <bool> prime;
vector <LL> primes,NOD,SPF_cnt;

void seive(LL n = 1<<20){
    prime.assign(n+1,true), NOD.resize(n+1), SPF_cnt.resize(n+1);
    NOD[1] = 1;
    for(LL i=2;i<=n;i++){
        if(prime[i]) {
        	SPF_cnt[i] = 1,NOD[i] = 2;
            primes.push_back(i);
        }
        for(auto p:primes){
            if(p*i>n)   break;
            prime[p*i] = false;

            if(i%p == 0){
            	SPF_cnt[p*i] = SPF_cnt[i] + 1;
            	NOD[p*i] = NOD[i]/(SPF_cnt[i]+1) * (SPF_cnt[i]+2);
            	break; 
            } else {
            	NOD[p*i] = NOD[p]*NOD[i];
            	SPF_cnt[p*i] = 1;
            }
        }
    }
}

int main()
{
	monke_flip
	seive();
	for(int i=1;i<100;i++){
		cout<<NOD[i]<<'\n';
	}
	return MONKE;
}