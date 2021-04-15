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

int main()
{
	monke_flip
	ll n,d;
	cin>>n>>d;
	vector <ll> v(n);
	for(auto &e:v){
		cin>>e;
	}
	sort(v.begin(), v.end());
	ll ans = 0;
	for(int l=0, r=0; l<n; l++){
		while(r+1 < n and v[l]+d>=v[r+1]) r++;
		ll len = r-l;
		ans+= len*(len-1)/2;
	}
	cout<<ans;
	return MONKE;
}