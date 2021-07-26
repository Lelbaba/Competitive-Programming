#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MONKE = 0;

const double PI = acos(-1), EPS = 1e-10;
#define sq(x) (x)*(x)

template <typename DT> 
class point{
    public:
        DT x,y;
    point() = default;
    point(DT x, DT y): x(x), y(y) {};
    
    point operator + (point rhs) const { return point(x + rhs.x, y + rhs.y); }
    point operator - (point rhs) const { return point(x - rhs.x, y - rhs.y); }

    point operator * (DT M)      const { return point(M * x, M * y); }
    point operator / (DT M)      const { return point(x / M, y / M); }
    bool  operator < (point rhs) const { return x < rhs.x or (x == rhs.x and y < rhs.y); }
    point operator == (point rhs) const { return x == rhs.x and y == rhs.y; }
    point operator != (point rhs) const { return x != rhs.x or y != rhs.y; } 
    DT operator & (point rhs)     const { return x * rhs.y - y * rhs.x; }     // cross product
    DT operator ^ (point rhs)     const { return x * rhs.x + y * rhs.y; }     // dot product
    DT operator ~()     const {return sq(x) + sq(y); }                        //square of norm
    point operator - () const {return *this * -1; }    
    friend istream& operator >> (istream &is, point &p) { return is >> p.x >> p.y; }
    friend ostream& operator << (ostream &os, const point &p) { return os << p.x << " " << p.y; }
    
    friend DT dis_sq(point a, point b){ return sq(a.x-b.x) + sq(a.y-b.y); }
    friend DT tri_area(point a,point b, point c){ return (b-a) & (c-a); }
    friend double angle(point u) { return atan2(u.y, u.x); }
    friend int dcmp(DT x) { return fabs(x) < EPS ? 0 : (x<0 ? -1 : 1);}
    friend double angle(point a, point b) {
        double ans = angle(b) - angle(a);
        return ans <= -PI ? ans + 2*PI : (ans > PI ? ans - 2*PI : ans);
    }
};
template <typename DT> 
struct polarComp {
    point  <DT> O, dir;
    polarComp(point <DT> O = point(0, 0), point <DT> dir = point(1, 0))
        : O(O), dir(dir) {}
    bool half(point  <DT> p) {
        return dcmp(dir & p) < 0 || (dcmp(dir & p) == 0 && dcmp(dir ^ p) > 0);
    }
    bool operator() (point <DT>p, point <DT> q) {
        return make_tuple(half(p), 0) < make_tuple(half(q), (p & q));
    }
};
template <typename DT> using polygon = vector <point <DT>>; 
int main()
{
    point <int> p;
    cin >> p ;
    polygon <int> z;
    cout << -p;
    return MONKE;
}