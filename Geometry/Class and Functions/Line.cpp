#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MONKE = 0;
const double eps = 1e-9;
template <typename DT> 
class point{
    public:
        DT x,y;
    point() = default;
    point(DT x, DT y) : x(x), y(y) {};
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
    bool operator < (point rhs) const {
        return x<rhs.x|| (x==rhs.x && y<rhs.y);
    }
    point operator == (point rhs) const {
        return x == rhs.x and y == rhs.y;
    } 
    DT operator & (point rhs){
        return (x*rhs.y- y*rhs.x);      // cross product
    }
    DT operator ^ (point rhs){
        return x*rhs.x + y*rhs.y;       // dot product 
    }
    friend DT dis_sq(point a, point b){
        return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
    }
    friend DT tri_area(point a,point b, point c){
        return (b-a) & (c-a);
    }
    friend istream& operator >> (istream& in, point &p){
        in >> p.x >> p.y;
        return in;
    }
    friend ostream& operator << (ostream& out, point p){
        out << p.x << ' ' << p.y;
        return out;
    }
};
template <typename DT>
class line{
    public:
        point <DT> dir, O; // direction of vector and starting point
    line(point <DT> p,point <DT> q){
        dir = q-p;
        O = p;
    }
    bool parallel(line &L){
        return fabs(dir & L.dir) < eps;
    }
    bool collinear(point <DT> &p){
        point <DT> tem = p - O;
        return fabs(dir & tem) < eps;
    }
    int intersection(line L, point <double> &p){
        if(parallel(L)){
            if(collinear(L.O)) return -1;
            return 0;
        }
        point <DT> R = L.O - O;
        double t = double(R & L.dir)/(dir & L.dir);
        point <double> ans(O.x,O.y), DIR(dir.x,dir.y);
        p = ans + (DIR*t);
        return 1;
    }
    line perp(point <DT> p){
        point <DT> tem(-dir.y,dir.x);
        return line(p,p+tem);
    }
};

int main()
{
    return MONKE;
}
