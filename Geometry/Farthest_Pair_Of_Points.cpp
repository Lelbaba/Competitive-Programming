#include <bits/stdc++.h>
using namespace std;


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

using pt = point <int>;
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

int Rotating_Callipars(vector <pt> p){
	int n = p.size();
	int ans = -1e9, j=1;
	for(int i=0;i<n;i++)
	{	
		while( abs(p[(j+1)%n].tri_area(p[i],p[(i+1)%n])) > abs(p[j].tri_area(p[i],p[(i+1)%n])) ) j = (j+1)%n;
		ans = max(ans,p[j].dis_sq(p[i]) );
		ans = max(ans,p[j].dis_sq(p[(i+1)%n]));
	}
	return ans;
}

int main()
{
	int n;
	scanf("%d", &n);
	vector <pt> V(n);
	for(auto &x:V) x.scan();
	printf("%.8lf", sqrt(Rotating_Callipars(Convex_Hull(V))) );
	return 0;
}
