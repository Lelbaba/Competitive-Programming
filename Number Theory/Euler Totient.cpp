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
//CF 1512 G

vector <bool> prime;
vector <LL> primes,phi;

void seive(LL n = 1<<20){
    prime.assign(n+1,true), phi.resize(n+1);
    phi[1] = 1;
    for(LL i=2;i<=n;i++){
        if(prime[i]) {
            phi[i] = i-1;
            primes.push_back(i);
        }
        for(auto p:primes){
            if(p*i>n)   break;
            prime[p*i] = false;
            if(i%p == 0){
                phi[p*i] = p*phi[i];
                break;
            } else {
                phi[p*i] = phi[p] * phi[i];
            }
        }
    }
}

int main()
{
    monke_flip
    int n = 1e7+5,t;
    seive(n);
    return MONKE;
}