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

template <typename DT> using polygon = vector <point <DT>>; 
namespace polygon_algo{
    template <typename DT> polygon <DT> Convex_Hull(polygon <DT> &PT){
        sort(PT.begin(), PT.end());
        int m = 0, n = PT.size();

        polygon <DT> hull(n+n+2);
        for(int i=0; i<n; i++){ 
            for( ; m > 1 and tri_area(hull[m-2], hull[m-1], PT[i]) <= 0; m-- );
            hull[m++] = PT[i];
        }
        for(int i = n-2, k = m; i >= 0; i--){
            for( ; m>k and tri_area(hull[m-2], hull[m-1], PT[i]) <= 0; m--);
            hull[m++] = PT[i];
        }
        if(n>1) 
            m--;
        while(hull.size() > m) 
            hull.pop_back();
        return hull;
    }

    template <typename DT> DT minimum_bounding_box(polygon <DT> P){
        auto p = Convex_Hull(P);
        int n = p.size();
        DT area = 1e20 + 5;
        for(int i = 0, l = 1, r = 1, u = 1 ;   i < n ;   i++){
            point <DT> edge = (p[(i+1)%n]- p[i])/sqrt(dis_sq(p[i], p[(i+1)%n]));

            for( ; (edge ^ p[r%n]-p[i]) < (edge ^ p[(r+1)%n] - p[i]); r++); 
            for( ; u<r || (edge & p[u%n] - p[i]) < (edge & p[(u+1)%n] - p[i]); u++) ;
            for( ; l<u || (edge ^ p[l%n] - p[i]) > (edge ^ p[(l+1)%n] - p[i]); l++);
            
            double w = (edge ^ p[r%n]-p[i]) - (edge ^ p[l%n] - p[i]);
            double h = fabs(tri_area(p[u%n], p[i], p[(i+1)%n]))/sqrt(dis_sq(p[i], p[(i+1)%n]));
            area = min(area,w*h);
        }
        if(area>1e19) 
            area = 0;
        return area;
    }
    template <typename DT> DT farthest_pair_of_points(polygon <DT> p){
        p = Convex_Hull(p);
        int n = p.size();
        DT ans = -1e9;
        for(int i=0, j = 1; i < n; i++)
        {   
            for( ; abs(tri_area(p[i], p[(i+1)%n], p[(j+1)%n])) > abs(tri_area(p[i], p[(i+1)%n], p[j])) ; j = (j+1)%n ) ;
            ans = max(ans, dis_sq(p[i], p[j]));
            ans = max(ans, dis_sq(p[(i+1)%n], p[j]));
        }
        return ans;
    }
};

int main()
{
    monke_flip
    
    return MONKE;
}