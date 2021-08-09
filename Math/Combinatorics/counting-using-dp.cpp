#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke chrono::system_clock::now().time_since_epoch().count()
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using ll = long long;
const int MONKE = 0;

/*
    Given n boxes, each box has cnt[i] different (distinct) items, 
    you can take only 1 object from each box. how many different combinations
    of choices are there  
*/
ll call(ll box, ll take, vector <ll> &cnt){
    vector < vector <int>> DP(box+1, vector <int> (take+2));
    dp[0][0] = 1, dp[0][1] = cnt[0];
    for(int s = 0; s <= take; s++){
        for(int idx = 0; idx < box; idx++){
            dp[idx+1][s] = ( dp[idx+1][s] + dp[idx][s]);
            dp[idx+1][s+1] = (dp[idx+1][s+1] + dp[idx][s] * cnt[idx+1][s]);
        }
    }
    return dp[box-1][take];
}

int main()
{
    monke_flip
    
    return MONKE;
}