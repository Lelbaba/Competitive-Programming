#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct point
{
	ll x,y;
	point(ll _x=0,ll _y=0) {x = _x,y = _y;}
	ll cross(const point &p){
		return ((x*p.y)-(y*p.x));
	}
	point operator - (point &p){
		return point(x-p.x,y-p.y); 
	}
	bool operator <(point &p){
		return (x<p.x) || (x==p.x && y<p.y);
	}
	void scan(){
		scanf("%lld%lld", &x,&y);
	}
};
ll area(point a,point b,point c){
	b=b-a,c=c-a;
	return b.cross(c);
}
int main()
{
	int n,m;
	scanf("%d%d", &n,&m);
	vector <point> red(n),blue(m);
	for(auto &e:red) e.scan();
	for(auto &e:blue) e.scan();
	sort(red.begin(),red.end());
	ll under[505][505];
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			under[i][j] = 0;
			for(auto e:blue){
				if(area(red[i],e,red[j])>0 && red[i].x <=e.x && e.x <red[j].x)
					under[i][j]++;
			}
		}
	}
	ll ans = 0;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			for(int k=j+1;k<n;k++){
				if(under[i][j]+under[j][k] == under[i][k])
					ans++;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
