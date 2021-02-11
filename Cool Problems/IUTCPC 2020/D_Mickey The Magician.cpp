#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll gooddays(vector <ll> &potion){
	ll last = ll(potion.size())-1;

	set <ll> after;

	vector <bool> day(last+1);
	vector <bool> night(last+1);
	vector <ll> day_next(last+1);
	vector <ll> night_next(last+1);
	map <ll,ll> min_next;
	after.insert(potion[last]); 
	min_next[potion[last]] = last;
	ll good = 1;
	day[last] = true;
	night[last] = true;
	for(ll i = last-1; i>=0;i--){
		auto it = lower_bound(after.begin(),after.end(),potion[i]);
		if(it == after.end()) day[i] = false;
		else{
			day_next[i] = min_next[*it];
			day[i] = night[day_next[i]];
			if(day[i]) good++;
		}
		if(*it>potion[i] && it == after.begin()) night[i] = false;
		else{
			if(*it>potion[i]) it--;
			night_next[i] = min_next[*it];
			night[i] = day[night_next[i]];
		}
		min_next[potion[i]] = i;
		after.insert(potion[i]);
	}
	return good;
}

int main()
{
	int t;
	cin>>t;
	while(t--){
		ll n;
		cin>>n;
		vector <ll> v(n);
		for(auto &x:v) cin>>x;
		ll k = gooddays(v);
		ll sum = 0;
		for(auto &x:v){
			sum+=x;
			x=sum;
		}
		ll i,j;
		ll low = 0;
		vector <ll> MIN(n);
		ll max_seg = 0;
		ll pre=max(0ll,sum),suf = max(0ll,sum);
		for(i=0;i<n;i++){
			MIN[i] = low;
			low = min(low,v[i]);
			max_seg = max(v[i]-MIN[i],max_seg);
			pre = max(pre,v[i]);
			suf = max(suf,sum-v[i]); 
		}
		ll ans = max_seg;
		if(k>1) ans = max(ans,pre+suf+(k-2)*max(0ll,sum));
		cout<<ans<<endl;
	}
	return 0;
}
