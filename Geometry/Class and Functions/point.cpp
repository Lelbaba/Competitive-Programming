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

int main()
{
    return MONKE;
}