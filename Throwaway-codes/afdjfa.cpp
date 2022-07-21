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

/*....................................................................*/ 

int main()
{
    monke_flip
    cout << 10000 << '\n';
    for(int i = 0; i < 10000; i++) {
        cout << 20 << '\n';
        for(int j = 0; j < 20; j++) 
            cout << uniform_int_distribution <int> (0, 10)(rng) << ' ';
        cout << '\n';
    }
    return MONKE;
}