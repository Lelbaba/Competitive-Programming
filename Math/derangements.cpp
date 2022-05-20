#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke chrono::system_clock::now().time_since_epoch().count()
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using LL = long long;
using ULL = unsigned long long;
mt19937_64 rng(random_monke);
const int MONKE = 0;

/*....................................................................*/ 
const int N = 1e5 + 5, mod = 1e9 + 7;
namespace drng {
    array <int, N + 1> Drng;
    void init(){
        Drng[0] = 1, Drng[1] = 0;
        for(int i = 2; i <= N; i++)
            Drng[i] = (LL) (i - 1) * (Drng[i - 1] + Drng[i - 2]) % mod;
    }
    int D(int n) { 
        return n < 0 ? 0 : Drng[n];
    }
}

/*....................................................................*/ 

int main()
{
    monke_flip
    
    return MONKE;
}