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

struct dt
{
	ll P,N,cnt;
};

int main()
{
	monke_flip
	
	string s;
	vector<dt> ing(3);
	ll money;
	
	cin>>s;
	for(auto &e:ing) cin>>e.N;
	for(auto &e:ing) cin>>e.P;
	cin>>money;

	for(auto x:s){
		if(x == 'B') ing[0].cnt++;
		else if (x == 'S') ing[1].cnt++;
		else ing[2].cnt++;
	}

	auto khoroch = [&](ll num){
		ll cost = 0;
		for(auto e:ing) cost += max(0ll,num*e.cnt - e.N)*e.P;
		return cost;
	};
	auto ok = [&](ll mid){
		return khoroch(mid)<=money;
	};
	ll lo = 0,hi = 1e15,ans = -1;
	while(lo<=hi){
		ll mid = lo + (hi-lo)/2;
		if(ok(mid)) {
			ans = mid;
			lo = mid+1;
		} else {
			hi = mid-1;
		}
	}
	cout<<ans;
	
	return MONKE;
}