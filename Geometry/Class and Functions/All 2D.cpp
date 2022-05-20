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
template <typename DT> DT sq(DT x) {return x * x; }
template <typename DT> int dcmp(DT x) { return fabs(x) < EPS ? 0 : (x<0 ? -1 : 1);}

template <typename DT> 
class point{
    public:
        DT x,y;
    point() = default;
    point(DT x, DT y): x(x), y(y) {};
    template <typename X> point(point <X> p): x(p.x), y(p.y) {};
    
    point operator + (const point &rhs) const { return point(x + rhs.x, y + rhs.y); }
    point operator - (const point &rhs) const { return point(x - rhs.x, y - rhs.y); }
    point operator * (const point &rhs) const { return point(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);}
    point operator / (const point &rhs) const { return *this * point(rhs.x, - rhs.y) / ~(rhs);}

    point operator * (DT M)      const { return point(M * x, M * y); }
    point operator / (DT M)      const { return point(x / M, y / M); }
    bool  operator < (point rhs) const { return x < rhs.x or (x == rhs.x and y < rhs.y); }
    point operator == (const point &rhs) const { return x == rhs.x and y == rhs.y; }
    point operator != (const point &rhs) const { return x != rhs.x or y != rhs.y; } 
    DT operator & (const point &rhs)     const { return x * rhs.y - y * rhs.x; }     // cross product
    DT operator ^ (const point &rhs)     const { return x * rhs.x + y * rhs.y; }     // dot product
    DT operator ~()     const {return sq(x) + sq(y); }                        //square of norm
    point operator - () const {return *this * -1; }    
    friend istream& operator >> (istream &is, point &p) { return is >> p.x >> p.y; }
    friend ostream& operator << (ostream &os, const point &p) { return os << p.x << " " << p.y; }
    
    friend DT dis_sq(const point &a, const point &b){ return sq(a.x-b.x) + sq(a.y-b.y); }
    friend DT tri_area(const point &a, const point &b, const point &c){ return (b-a) & (c-a); }
    friend double angle(const point &u) { return atan2(u.y, u.x); }
    friend double angle(const point &a, const point &b) {
        double ans = angle(b) - angle(a);
        return ans <= -PI ? ans + 2*PI : (ans > PI ? ans - 2*PI : ans);
    }
    friend point perp(const point &a){
        return point(-a.y, a.x);
    }
};
template <typename DT> 
class polarComp {
    point <DT> O, dir;
    bool half(point  <DT> p) {
        return dcmp(dir & p) < 0 || (dcmp(dir & p) == 0 && dcmp(dir ^ p) > 0);
    }
    public:
    polarComp(point <DT> O = point(0, 0), point <DT> dir = point(1, 0))
        : O(O), dir(dir) {}
  
    bool operator() (point <DT>p, point <DT> q) {
        return make_tuple(half(p), 0) < make_tuple(half(q), (p & q));
    }
};

template <typename DT>
class line{
    public:
        point <DT> dir, O; // direction of vector and starting point
    line(point <DT> p,point <DT> q): dir(q - p), O(p) {};

    bool contains(const point <double> &p){ 
        return fabs(p - O & dir ) < EPS;
    } // checks whether the line contains a certain point
    template <typename XT> point <XT> at(XT t){
        return point <XT> (dir) * t + O;
    } // inserts value of t in the vector representation, finds the point which is O + Dir*t
    double inv_at(const point <double> &p){
        assert(contains(p));
        return (p - O).x / dir.x;
    } // if the line contains a point, gives the value t such that, p = O+Dir*t
    line perp(point <DT> p){
        return line(p, p + (-dir.y,dir.x));
    }
    friend bool parallel(line& L, line& R){
        return fabs(R.dir & L.dir) < EPS;
    }
    friend int intersects(line& L, line& R){
        return parallel(L, R) ? R.contains(L.O) ? -1 : 0 : 1;
    }
    friend pair <double, double> intersection_at(line &L, line &R){
        double r = double((L.O - R.O) & L.dir)/(R.dir & L.dir);
        double l = double((R.O - L.O) & R.dir)/(L.dir & R.dir);
        return {l, r};
    }
    friend pair <int, point<double>> intersection_point(line L, line R,int _L = 0, int _R = 0){
        // _L and _R can be 0 to 3, 0 is a normal line, 3 is a segment, 1 and 2 are rays (considered bitwise)
        int ok = intersects(L, R);
        if(ok == 0)
            return {0, {0, 0}};
        if(ok == 1){
            auto [l,r] = intersection_at(L, R);
            if(l < (0-EPS) and _L & 2 )
                return {0, {0, 0}};
            if(l > (1+EPS) and _L & 1)
                return {0, {0, 0}};
            if(r < (0-EPS) and _R & 2 )
                return {0, {0, 0}};
            if(r > (1+EPS) and _R & 1)
                return {0, {0, 0}};
            return {1, L.at(l)};
        }
        return {-1, {0,0}}; // they are the same line
    }
    friend double dis_of_point(const line <DT> &L, const point <DT> &P) {
        return fabs(L.dir & (P - L.O))/sqrt(~(L.dir));   
    }
};
template <typename DT> 
class circle {
    public:
        point <DT> O;
        DT R;
    circle(const point <DT> &O,  DT R) : O(O), R(R) {}
    // the next two make sense only on circle <double>
    circle(const point <DT> &A, const point <DT> &B, const point <DT> &C){
        point <DT> X = (A + B) / 2, Y = (B + C) / 2, d1 = perp(A - B), d2 = perp(B - C);
        O = intersection_point(line(X, d1), line(Y, d2)).second;
        R = sqrt(~(O - A));
    }
    circle(const point <DT> &A, const point <DT> &B, DT R){
        point <DT> X = (A + B) / 2, d = perp(A - B);
        d = d * (R / sqrt(~(d)));
        O = X + d;
        R = sqrt(~(O - A));
    }
    friend tuple <int, point <DT>, point <DT>> intersection_point(const circle &a,const circle &b) {
        if(a.r == b.r and a.O == b.O)
            return {-1, {0, 0}, {0, 0}};
        double d = sqrt(dis_sq(a.O, b.O));
        if(d > a.r + b.r or d < fabs(a.r - b.r))
            return {0, {0, 0}, {0, 0}};
        double z = (sq(a.r) + sq(d) - sq(b.r)) / (2 * d);
        double y = sqrt(sq(a.r) - sq(d));
        point <DT> O = b.O - a.O, h = perp(O) * (y / sqrt(~O));
        O = a.O + O * (z / sqrt(~O));
        return make_tuple(1 + (~(h) > EPS), O + h, O - h);
    }


};
template <typename DT> using polygon = vector <point <DT>>; 

namespace polygon_algo{
    template <typename DT> polygon <DT> Convex_Hull(polygon <DT> &PT){
        sort(PT.begin(), PT.end());
        int m = 0, n = PT.size();

        polygon <DT> hull(n + n + 2);
        for(int i = 0; i < n; i++){ 
            for( ; m > 1 and tri_area(hull[m-2], hull[m-1], PT[i]) <= 0; m-- );
            hull[m++] = PT[i];
        }
        for(int i = n - 2, k = m; i >= 0; i--){
            for( ; m > k and tri_area(hull[m - 2], hull[m - 1], PT[i]) <= 0; m--);
            hull[m++] = PT[i];
        }
        if(n>1) 
            m--;
        while(hull.size() > m) 
            hull.pop_back();
        return hull;
    }

    template <typename DT> double minimum_bounding_box(polygon <DT> P){
        auto p = Convex_Hull(P);
        int n = p.size();
        double area = 1e20 + 5;
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
    template <typename DT> DT farthest_pair_of_points_sq(polygon <DT> p){
        p = Convex_Hull(p);
        int n = p.size();
        DT ans = -1e9;
        for(int i=0, j = 1; i < n; i++)
        {   
            for( ; abs(tri_area(p[i], p[(i+1)%n], p[(j+1)%n])) > abs(tri_area(p[i], p[(i+1)%n], p[j])) ; j = (j+1)%n ) ;
            ans = max(ans, dis_sq(p[i], p[j]));
            ans = max(ans, dis_sq(p[(i+1)%n], p[j]));
        }
        return ans; // will return square of the answer.
    }
}

int main()
{
    monke_flip
    point <double> a(0, 5), b(0, 5), c(-3, 4), d(4, 3), e(-4, -3);
    circle <double> A(a, b, c), B(c, d, e), C(b, d, e);
    dbg(A.O, B.O, C.O);
    dbg(A.R, B.R, C.R);
    line <double> L({0, 0}, {1, 1});
    cout << dis_of_point(L, {-1, 1});
    polygon <int> P;
    P.emplace_back(1, 2);
    P.emplace_back(-3, 4);
    P.emplace_back(0, -5);

    return MONKE;
}