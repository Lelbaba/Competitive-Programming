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
using ld = long double;
const int MONKE = 0;
const double eps = 1e-9;
using dt = double;
// UVA 10173
template <typename DT> 
class point{
    public:
        DT x,y;
    point(DT X = 0,DT Y = 0) {
        x=X, y=Y;
    }
    point operator + (point rhs) {
        return point(x+rhs.x,y+rhs.y);
    }
    point operator - (point rhs){
        return point(x-rhs.x,y-rhs.y);
    }
    point operator * (DT M){
        return point(M*x,M*y);
    }
    point operator / (DT M){
        return point(x/M,y/M);
    }
    bool operator < (point rhs) {
        return x<rhs.x|| (x==rhs.x && y<rhs.y);
    }
    DT cross(point rhs){
        return (x*rhs.y- y*rhs.x);
    }
    DT dis_sq(point rhs){
        return (x-rhs.x)*(x-rhs.x) + (y-rhs.y)*(y-rhs.y);
    }
    DT tri_area(point a,point b){
        return (a-*this).cross((b-*this));
    }
    DT dot(point rhs){
        return x*rhs.x + y*rhs.y; 
    }
    void scan(){
        cin>>x>>y;
    }
};

using pt = point <double>;
vector <pt> Convex_Hull(vector <pt> &points){

	sort(points.begin(),points.end());
	int m=0, n=points.size();
	vector <pt> hull(n+n+2);
	for(int i=0;i<n;i++){ 
		while(m>1 && (hull[m-2].tri_area(hull[m-1],points[i]))<=0 ) m--;
		hull[m++] = points[i];
	}
	int k=m;
	for(int i=n-2;i>=0;i--){
		while(m>k && (hull[m-2].tri_area(hull[m-1],points[i]))<=0) m--;
		hull[m++] = points[i];
	}
	if(n>1) m--;
	while(hull.size()>m) hull.pop_back();
	return hull;
}
double rotating_calipers(vector <pt> &p){
	int n = p.size(), l=1, r=1, u=1;
	double area = 1e20;
	for(int i=0;i<n;i++){
		pt edge = (p[(i+1)%n]- p[i])/sqrt(p[i].dis_sq(p[(i+1)%n]));

		while(edge.dot(p[r%n]-p[i]) < edge.dot(p[(r+1)%n]-p[i])) r++;
		while(u<r || edge.cross(p[u%n]-p[i]) < edge.cross(p[(u+1)%n]-p[i])) u++;
		while(l<u || edge.dot(p[l%n]-p[i]) > edge.dot(p[(l+1)%n]-p[i])) l++;
		
		double w = edge.dot(p[r%n]-p[i]) - edge.dot(p[l%n]-p[i]);
		double h = fabs(p[u%n].tri_area(p[i],p[(i+1)%n]))/sqrt(p[i].dis_sq(p[(i+1)%n]));
		area = min(area,w*h);
	}
	if(area>1e19) area = 0;
	return area;
}
int main()
{
	int n;
	monke_flip
	while(true){
		cin>>n;
		if(n==0) break;
		vector <pt> v(n);
		for(auto &e:v) e.scan();
		auto hull = Convex_Hull(v);
		double area = rotating_calipers(hull);
		cout<<fixed<<setprecision(4)<<area<<'\n';
	}
	return 0;
}
