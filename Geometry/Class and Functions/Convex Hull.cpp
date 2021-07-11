#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MONKE = 0;


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
    DT operator & (point rhs){
        return (x*rhs.y- y*rhs.x);      // cross product
    }
    DT operator ^ (point rhs){
        return x*rhs.x + y*rhs.y;       // dot product 
    }
    DT dis_sq(point rhs){
        return (x-rhs.x)*(x-rhs.x) + (y-rhs.y)*(y-rhs.y);
    }
    DT tri_area(point a,point b){
        return a-*this & b-*this; // 2* tri_area
    }
};
using pt = point <double>;
vector <pt> Convex_Hull(vector <pt> &points){

    sort(points.begin(),points.end());
    int m=0, n=points.size();
    vector <pt> hull(n+n+2);
    for(int i=0;i<n;i++){ 
        while(m>1 and (hull[m-2].tri_area(hull[m-1],points[i]))<=0 ) m--;
        hull[m++] = points[i];
    }
    int k=m;
    for(int i=n-2;i>=0;i--){
        while(m>k and (hull[m-2].tri_area(hull[m-1],points[i]))<=0) m--;
        hull[m++] = points[i];
    }
    if(n>1) m--;
    while(hull.size()>m) hull.pop_back();
    return hull;
}
int main()
{
    return MONKE;
}