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


void solve(){
    int n;
    cin >> n;
    vector <int> v(n), night(n, -1), day(n, -1), pref(n), suf(n);
    for(auto &e:v){
        cin >> e;
    }
    map <int,int> visited;
    int k = 1;
    visited[v[n-1]] = day[n-1] = night[n-1] = n-1; 
    for(int i = n-2; i >= 0; i--){
        auto greater = visited.lower_bound(v[i]);
        if(greater != visited.end())
            day[i] = night[greater -> second];
        auto smaller = visited.upper_bound(v[i]);
        if(smaller != visited.begin())
            night[i] = day[prev(smaller) -> second];
        visited[v[i]] = i;
        k += day[i] != -1;
    }
    partial_sum(v.begin(), v.end(), pref.begin());
    partial_sum(v.rbegin(), v.rend(), suf.rbegin());
    
    ll MAX = 0, low = 0;
    for(auto e:pref){
        MAX = max(MAX, e - low);
        low = min((ll) e, low);
    }
    
    if(k > 1){
        ll pref_max = max(0, *max_element(pref.begin(),pref.end()));
        ll suf_max = max(0, *max_element(suf.begin(), suf.end()));

        MAX = max( pref_max + suf_max +  max(0ll, (ll) pref[n-1] * (k-2)),  MAX ); 
    }
    cout << MAX << '\n';
}

int main()
{
    monke_flip
    int t = 1; 
    cin>>t;
    for(int tc=1; tc<=t; tc++){
        solve();
    }
    return MONKE;
}