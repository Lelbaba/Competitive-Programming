#include <bits/stdc++.h>
using namespace std;
using dt = double;
// UVA 10173
struct point{
	dt x,y;
	point(double X = 0,double Y = 0) {x=X, y=Y;}
	point operator + (const point &rhs) {return point(x+rhs.x,y+rhs.y);}
	point operator - (const point &rhs) {return point(x-rhs.x,y-rhs.y);}
	point operator * (dt m) {return point(x*m, y*m);}
	point operator / (dt m) {return point(x/m, y/m);}
	dt cross(const point &p){return (x*p.y - y*p.x);}
	dt dot(const point &p) {return (x*p.x+y*p.y);}
	bool operator < (const point &rhs) {return x<rhs.x|| (x==rhs.x && y<rhs.y);}
	dt dis(const point &rhs) {return hypot(x-rhs.x,y-rhs.y);}
	dt area(point a,point b){
		return (a-*this).cross(b-*this);
	}
	void scan(){
		scanf("%lf %lf", &x,&y);
	}
};

vector <point> Convex_Hull(vector <point> &points){

	sort(points.begin(),points.end());
	int m=0, n=points.size();
	vector <point> hull(n+n+2);
	for(int i=0;i<n;i++){ 
		while(m>1 && (hull[m-2].area(hull[m-1],points[i]))<=0 ) m--;
		hull[m++] = points[i];
	}
	int k=m;
	for(int i=n-2;i>=0;i--){
		while(m>k && (hull[m-2].area(hull[m-1],points[i]))<=0) m--;
		hull[m++] = points[i];
	}
	if(n>1) m--;
	while(hull.size()>m) hull.pop_back();
	return hull;
}
double rotating_calipers(vector <point> &p){
	int n = p.size(), l=1, r=1, u=1;
	double area = 1e20;
	for(int i=0;i<n;i++){
		point edge = (p[(i+1)%n]- p[i])/p[i].dis(p[(i+1)%n]);

		while(edge.dot(p[r%n]-p[i]) < edge.dot(p[(r+1)%n]-p[i])) r++;
		while(u<r || edge.cross(p[u%n]-p[i]) < edge.cross(p[(u+1)%n]-p[i])) u++;
		while(l<u || edge.dot(p[l%n]-p[i]) > edge.dot(p[(l+1)%n]-p[i])) l++;
		printf("%d %d %d %d\n", i,r,u,l);
		double w = edge.dot(p[r%n]-p[i]) - edge.dot(p[l%n]-p[i]);
		double h = fabs(p[u%n].area(p[i],p[(i+1)%n]))/p[i].dis(p[(i+1)%n]);
		area = min(area,w*h);
	}
	if(area>1e19) area = 0;
	return area;
}
int main()
{
	int n;
	while(true){
		scanf("%d", &n);
		if(n==0) break;
		vector <point> v(n);
		for(auto &e:v) e.scan();
		auto hull = Convex_Hull(v);
		double area = rotating_calipers(hull);
		printf("%.4lf\n", area);
	}
	return 0;
}
