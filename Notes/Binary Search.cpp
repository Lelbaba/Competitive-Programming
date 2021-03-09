/*
***************************
BINARY PROPERTY

Binary property refers to a property of a sequence that is true for all values <=x for some x and false forall values >x, ie

bool func(val)
	true if val <= x
	false if val > x

In these special cases we can easily find the exact point where the property switches

while hi>=lo:
	if(ok(mid)) lo = mid+1
	else hi = mid -1

lo will be the first number where the property is false
hi will be the last number where the property is true

****************************
On the other hand you can take a reverse property that switches on after a certain range

then 

while hi>=lo:
	if(ok(mid)) hi = mid-1
	else lo = mid+1

hi -> last number where property is not true
lo -> first number where property is true

****************************
The best approach might be to store the ans on another variable entirely while searching

Example code in c++
*/
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int MONKE = 0;

int main()
{
	int n;
	cin>>n;
	vector <int> v(n);
	for(auto &e:v) cin>>e;
	sort(v.begin(),v.end());
	auto ok = [&](int pos,int find){
		return v[pos]<=find;			// 1
	};
	auto search = [&](int x){
		int lo = 0,hi = v.size()-1;
		while(lo<=hi){
			int mid = lo+hi>>1;
			if(ok(mid,x)) lo =mid+1;
			else hi = mid-1;
		}
		return v[lo];				// 2
	};
	/*
		< and lo -> smallest element >= x
		<= and lo -> smallest element > x
		< and hi -> greatest element < x
		<= and hi -> greatest element <= x 

	*/
	int q;
	cin>>q;
	while(q--){
		int x;
		cin>>x;
		cout<<search(x)<<endl;
	}
	return MONKE;
}
