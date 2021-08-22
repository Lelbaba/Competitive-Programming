#include <bits/stdc++.h>
using namespace std;
using LL = long long;
struct point
{
	LL x,y;
	point(LL _x=0,LL _y=0) {x=_x, y=_y;}
	LL dis_sq(point p){
		return (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y);
	}
	bool operator < (const point &p){
		return (x<p.x || (x==p.x && y<p.y));
	}
};

LL sq(LL x) {return x*x;}

LL min_dis_sq(vector <point> &v){
	int n = v.size();
	sort(v.begin(),v.end());
	auto cmp = [](point a,point b){return (a.y<b.y || (a.y==b.y && a.x<b.x));};
	set <point, decltype(cmp)> s(cmp);

	LL best = 1e18;
	int j = 0;
	for(int i=0;i<n;i++){
		while(sq(v[i].x - v[j].x)>= best){
			s.erase(v[j]);
			j=(j+1)%n;
		}
		LL d = ceil(sqrt(best));
		auto it1 = s.lower_bound( point(v[i].x,v[i].y-d) );
		auto it2 = s.upper_bound( point(v[i].x,v[i].y+d) );
		for(auto it = it1;it!=it2;it++){
			LL dx = v[i].x - it->x;
			LL dy = v[i].y - it->y;
			best = min(best, sq(dx)+sq(dy));
		}
		s.insert(v[i]);
	}
	return best;
}

int main()
{
	int n,a;
	scanf("%d", &n);
	vector <point> v(n);
	int sum = 0;
	for(int i=1;i<=n;i++){
		scanf("%d", &a);
		sum += a;
		v[i-1] = point(i,sum);
	}
	printf("%lld\n", min_dis_sq(v));
	return 0;
}