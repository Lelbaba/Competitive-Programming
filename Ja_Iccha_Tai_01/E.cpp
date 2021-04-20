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
const double pi = acos(-1);
class circle{
	public:
		ll x,y,r;

	circle(ll x = 0,ll y = 0,ll r = 0){
		this->x = x, this-> y = y, this->r = r;
	}
	double area(){
		return pi*r*r;
	}
	bool contains(circle &rhs){
		ll dx = (x - rhs.x), dy = (y - rhs.y);
		return dx*dx + dy*dy <= r*r and r>rhs.r; 
	}
};

int main()
{
	monke_flip
	int n;
	cin>>n;
	vector <circle> v(n);
	vector <int> in(n);
	for(int i = 0; i < n; i++){
		cin >>v[i].x >>v[i].y >>v[i].r;
		for(int j = 0; j < i; j++){
			if(v[i].contains(v[j]) ){
				in[j]++;
			} else if( v[j].contains(v[i]) ){
				in[i]++; 
			}
		}
	}
	double ans = 0;
	for(int i=0;i<n;i++){
		(in[i] == 0 or in[i] & 1 ) ? ans += v[i].area() : ans -= v[i].area();
	}
	cout<<fixed<<setprecision(10)<<ans<<'\n';
	return MONKE;
}