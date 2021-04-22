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
/*

	Let's choose a point 'a_0' on the convex hull.
	what are the points 'b_0' and 'c_0' such that the area of the triangle is maximum?

	Key observation: Let's choose another point b, and try to find the point c such that the area is maximized.
	Point c will be one of the final points(c_0) that maximize the area for a specific a_0. We can find b_0 similarly.
	Now just iterate over all positions for a_0.
	To minimize complexity, something similar to 2 pointers has been used. (Rotating Calipers)

*/

int Find_Triangle(vector <pt> &v){
	int n = v.size();
	int i=0,j=1,k=2;
	int ans = -1e9;
	for(int i=0;i<n;i++){
		while(v[i].tri_area(v[j],v[k]) < v[i].tri_area(v[(j+1)%n],v[k]) ) j = (j+1)%n;
		while(v[i].tri_area(v[j],v[k]) < v[i].tri_area(v[j],v[(k+1)%n]) ) k = (k+1)%n;
		ans = max(ans,v[i].tri_area(v[j],v[k]));
	}
	return ans;
}

void solve(int &n){
	vector <pt> V(n);
	for(auto &x:V) x.scan();
	V = Convex_Hull(V);
	double ans = double(Find_Triangle(V))/2;
	printf("%.2lf\n", ans);
}

int main()
{
	int n;
	while(cin>>n){
		if(n==-1) break;
		solve(n);
	}
	return 0;
}
