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
const int MONKE = 0;


#define sq(x) (x)*(x)
template <typename DT> 
class point{
    public:
        DT x, y, z;
    point() = default;
    point(DT x, DT y, DT z): x(x), y(y), z(z) {};
    
    point operator + (point rhs) const { return point(x + rhs.x, y + rhs.y, z + rhs.z); }
    point operator - (point rhs) const { return point(x - rhs.x, y - rhs.y, z - rhs.z); }
    point operator * (DT M)      const { return point(M * x, M * y, M * z); }
    point operator / (DT M)      const { return point(x / M, y / M, z / M); }
    bool  operator < (point rhs) const { return make_tuple(x, y, z) < make_tuple(rhs.x, rhs.y, rhs.z); }
    point operator == (point rhs) const { return x == rhs.x and y == rhs.y; }
    point operator != (point rhs) const { return x != rhs.x or y != rhs.y; } 
    point operator & (point rhs)  const { return point(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x); }     // cross product
    DT operator ^ (point rhs)     const { return x * rhs.x + y * rhs.y + z*rhs.z; }     // dot product
    DT operator ~ () const {return sq(x) + sq(y) + sq(z); }                            //square of norm
    point operator - () const {return *this * -1; }    

    friend istream& operator >> (istream &is, point &p) { return is >> p.x >> p.y >> p.z; }
    friend ostream& operator << (ostream &os, const point &p) { return os << p.x << " " << p.y << " " << p.z; }
    
    friend DT dis_sq(point a, point b){ return sq(a.x-b.x) + sq(a.y-b.y); }
    friend DT tri_area(point a,point b, point c){ return sqrt(~(b-a) & (c-a)); }
};
int main()
{
    monke_flip
    return MONKE;
}