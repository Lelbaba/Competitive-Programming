#include <bits/stdc++.h>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#ifdef LEL
#include "dbg.h"
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using ll = long long;
const int MONKE = 0;
//LOJ- Solutions to an Equation
ll egcd(ll a,ll b,ll& x, ll& y){
	if(b==0){
		x = 1,y = 0;
		return a;
	}
	ll _x=1,_y=1,d = egcd(b,a%b,_x,_y);
	x = _y, y = _x - _y * (a/b);
	return d;
}
bool get_solution(ll a,ll b,ll c,ll& x,ll& y,ll& g){
	g = egcd(abs(a),abs(b),x,y);
	x *= c/g, y*= c/g;
	if(a<0) x = -x;
	if(b<0) y = -y;
	return c%g == 0;
}

void shift(ll a,ll b,ll& x,ll& y,ll k){
	x+=k*b,y-=k*a;
}
ll solutions_in_range(ll a,ll b,ll c,ll minx, ll maxx,ll miny,ll maxy){
	ll x,y,g;
	if(a==0 and b==0){
		if(c!=0) return 0;
		return (maxx-minx+1)*(maxy-miny+1);
	}
	if(a==0){
		if(c%b!=0 or maxy < c/b or miny > c/b) return 0;
		return (maxx-minx+1);
	}
	if(b==0){
		if(c%a!=0 or maxx < c/a or minx > c/a) return 0;
		return (maxy-miny+1);
	}
	
	if(!get_solution(a,b,c,x,y,g)){
		return 0;
	}
	a/=g,b/=g;
	shift(a,b,x,y,(minx-x)/b);
	if(x<minx){
		shift(a,b,x,y,b/abs(b));
	}
	ll xleft = x;
	if(x>maxx) return 0;

	shift(a,b,x,y,(maxx-x)/b);
	if(x>maxx){
		shift(a,b,x,y,-b/abs(b));
	}
	ll xright = x;
	
	shift(a,b,x,y,-(miny-y)/a);
	if(y<miny){
		shift(a,b,x,y,-a/abs(a));
	}
	if(y>maxy) return 0;
	ll _xleft = x;
	shift(a,b,x,y,-(maxy-y)/a);

	if(y>maxy){
		shift(a,b,x,y,a/abs(a));
	}
	ll _xright = x;

	if(xleft>xright) swap(xleft,xright);
	if(_xleft>_xright) swap(_xleft,_xright);
	xleft = max(xleft,_xleft),xright = min(xright,_xright);
	if(xleft>xright) return 0;
	return (xright-xleft)/abs(b)+1;
}
int main()
{
	int t;
	cin>>t;
	for(int tc = 1;tc<=t;tc++){
		ll a,b,c,mx,my,Mx,My;
		cin>>a>>b>>c>>mx>>Mx>>my>>My;
		c = -c;
		cout<<"Case "<<tc<<": "<<solutions_in_range(a,b,c,mx,Mx,my,My)<<endl;
	}
	return MONKE;
}