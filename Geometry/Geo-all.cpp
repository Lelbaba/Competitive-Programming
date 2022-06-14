#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke chrono::system_clock::now().time_since_epoch().count()
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using LL = long long;
using ULL = unsigned long long;
mt19937_64 rng(random_monke);
const int MONKE = 0;

/*....................................................................*/ 
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
    bool operator == (const point &rhs) const { return x == rhs.x and y == rhs.y; }
    bool operator <= (const point &rhs) const { return *this < rhs or *this == rhs; }
    bool operator != (const point &rhs) const { return x != rhs.x or y != rhs.y; } 
    DT operator & (const point &rhs)     const { return x * rhs.y - y * rhs.x; }     // cross product
    DT operator ^ (const point &rhs)     const { return x * rhs.x + y * rhs.y; }     // dot product
    DT operator ~()     const {return sq(x) + sq(y); }                        //square of norm
    point operator - () const {return *this * -1; }    
    friend istream& operator >> (istream &is, point &p) { return is >> p.x >> p.y; }
    friend ostream& operator << (ostream &os, const point &p) { return os << p.x << " " << p.y; }
    
    friend DT DisSq(const point &a, const point &b){ return sq(a.x-b.x) + sq(a.y-b.y); }
    friend DT TriArea(const point &a, const point &b, const point &c) { return (b-a) & (c-a); }
    friend DT UTriArea(const point &a, const point &b, const point &c) { return abs(TriArea(a, b, c)); }
    friend bool Collinear(const point &a, const point &b, const point &c) { return UTriArea(a, b, c) < EPS; }
    friend double Angle(const point &u) { return atan2(u.y, u.x); }
    friend double Angle(const point &a, const point &b) {
        double ans = Angle(b) - Angle(a);
        return ans <= -PI ? ans + 2*PI : (ans > PI ? ans - 2*PI : ans);
    }
    friend point Perp(const point &a){
        return point(-a.y, a.x);
    }
};
template <typename DT> using polygon = vector <point <DT>>; 
template <typename DT> 
class polarComp {
    point <DT> O, dir;
    bool half(point  <DT> p) {
        return dcmp(dir & p) < 0 || (dcmp(dir & p) == 0 && dcmp(dir ^ p) > 0);
    }
    public:
    polarComp(point <DT> O = point(0, 0), point <DT> dir = point(1, 0))
        : O(O), dir(dir) {}
  
    bool operator() (point <DT> p, point <DT> q) {
        return make_tuple(half(p), 0) < make_tuple(half(q), (p & q));
    }
}; // given a pivot point and an initial direction, sorts by Angle with the given direction

template <typename DT>
class line{
    public:
        point <DT> dir, O; // direction of vector and starting point
    line(point <DT> p,point <DT> q): dir(q - p), O(p) {};

    bool Contains(const point <double> &p){ 
        return fabs(p - O & dir ) < EPS;
    } // checks whether the line Contains a certain point
    template <typename XT> point <XT> At(XT t){
        return point <XT> (dir) * t + O;
    } // inserts value of t in the vector representation, finds the point which is O + Dir*t
    double AtInv(const point <double> &p){
        return abs(dir.x) > 0 ? (p - O).x / dir.x : (p - O).y / dir.y;
    } // if the line Contains a point, gives the value t such that, p = O+Dir*t
    line Perp(point <DT> p){
        return line(p, p + (-dir.y,dir.x));
    }
    point <DT> ProjOfPoint(const point <DT> &P) {
        return O + dir * ((P - O) ^ dir) / (~dir);
    }
    double DisOfPoint(const point <DT> &P) {
        return fabs(dir & (P - O))/sqrt(~(dir));   
    }
    friend bool Parallel(line& L, line& R){
        return fabs(R.dir & L.dir) < EPS;
    }
    friend int Intersects(line& L, line& R){
        return Parallel(L, R) ? R.Contains(L.O) ? -1 : 0 : 1;
    }
    friend pair <double, double> IntersectionAt(line &L, line &R){
        double r = double((L.O - R.O) & L.dir)/(R.dir & L.dir);
        double l = double((R.O - L.O) & R.dir)/(L.dir & R.dir);
        return {l, r};
    }
    friend pair <int, point<double>> IntersectionPoint(line L, line R,int _L = 0, int _R = 0){
        // _L and _R can be 0 to 3, 0 is a normal line, 3 is a segment, 1 and 2 are rays (considered bitwise)
        int ok = Intersects(L, R);
        if(ok == 0)
            return {0, {0, 0}};
        if(ok == 1){
            auto [l,r] = IntersectionAt(L, R);
            if(l < (0-EPS) and _L & 2 )
                return {0, {0, 0}};
            if(l > (1+EPS) and _L & 1)
                return {0, {0, 0}};
            if(r < (0-EPS) and _R & 2 )
                return {0, {0, 0}};
            if(r > (1+EPS) and _R & 1)
                return {0, {0, 0}};
            return {1, L.At(l)};
        }
        return {-1, {0,0}}; // they are the same line
    }
};
template <typename DT> 
class circle {
    public:
        point <DT> O;
        DT R;
    circle(const point <DT> &O = {0, 0},  DT R = 0) : O(O), R(R) {}
    // the next two make sense only on circle <double>
    circle(const point <DT> &A, const point <DT> &B, const point <DT> &C){
        point <DT> X = (A + B) / 2, Y = (B + C) / 2, d1 = Perp(A - B), d2 = Perp(B - C);
        O = IntersectionPoint(line(X, d1), line(Y, d2)).second;
        R = sqrt(~(O - A));
    }
    circle(const point <DT> &A, const point <DT> &B, DT R){
        point <DT> X = (A + B) / 2, d = Perp(A - B);
        d = d * (R / sqrt(~(d)));
        O = X + d;
        R = sqrt(~(O - A));
    }
    double SectorArea(double ang) {
        // Area of a sector of cicle
        return ang* R * R * .5;
    }
    double SectorArea(const point <DT> &a, const point <DT> &b) {
        return SectorArea(Angle(a - O, b - O));
    }
    double ChordArea(const point <DT> &a, const point <DT> &b) {
        // Area between sector and its chord
        return SectorArea(a, b) - 0.5 * TriArea(O, a, b);
    }
    int Contains(const point <DT> &p){
        // 0 for outside, 1 for inside, -1 for on the circle
        DT d = DisSq(O, p);
        return d > R * R ? 0 : (d == R * R ? -1 : 1);
    }
    friend tuple <int, point <DT>, point <DT>> IntersectionPoint(const circle &a,const circle &b) {
        if(a.R == b.R and a.O == b.O)
            return {-1, {0, 0}, {0, 0}};
        double d = sqrt(DisSq(a.O, b.O));
        if(d > a.R + b.R or d < fabs(a.R - b.R))
            return {0, {0, 0}, {0, 0}};
        double z = (sq(a.R) + sq(d) - sq(b.R)) / (2 * d);
        double y = sqrt(sq(a.R) - sq(z));
        point <DT> O = b.O - a.O, h = Perp(O) * (y / sqrt(~O));
        O = a.O + O * (z / sqrt(~O));
        return make_tuple(1 + (~(h) > EPS), O - h, O + h);
    }
    friend tuple <int, point <DT>, point <DT>> IntersectionPoint(const circle &C, line <DT> L) {
        point <DT> P = L.ProjOfPoint(C.O);
        double D = DisSq(C.O, P);
        if(D > C.R * C.R)
            return {0, {0, 0}, {0, 0}};
        double x = sqrt(C.R * C.R - D); 
        point <DT> h = L.dir * (x / sqrt(~L.dir));
        return {1 + (x > EPS), P - h, P + h};
    } 
    double SegmentedArea(point <DT> &a,  point <DT> &b) {
        // signed area of the intersection between the circle and triangle OAB
        double ans = SectorArea(a, b);
        line <DT> L(a, b);
        auto [cnt, p1, p2] = IntersectionPoint(*this, L);
        if(cnt < 2)
            return ans;
        double t1 = L.AtInv(p1), t2 = L.AtInv(p2);
        if(t2 < 0 or t1 > 1)
            return ans;
        if(t1 < 0)
            p1 = a;
        if(t2 > 1)
            p2 = b;
        return ans - ChordArea(p1, p2);
    }
};

namespace polygon_algo{
    template <typename DT> polygon <DT> ConvexHull(polygon <DT> &PT){
        sort(PT.begin(), PT.end());
        int m = 0, n = PT.size();
        
        polygon <DT> hull(n + n + 2);
        for(int i = 0; i < n; i++){ 
            for( ; m > 1 and TriArea(hull[m-2], hull[m-1], PT[i]) <= 0; m-- );
            hull[m++] = PT[i];
        }
        for(int i = n - 2, k = m; i >= 0; i--){
            for( ; m > k and TriArea(hull[m - 2], hull[m - 1], PT[i]) <= 0; m--);
            hull[m++] = PT[i];
        }
        if(n > 1) 
            m--;
        while(hull.size() > m) 
            hull.pop_back();
        return hull;
    }

    template <typename DT> double MinimumBoundingBox(polygon <DT> P){
        auto p = ConvexHull(P);
        int n = p.size();
        double area = 1e20 + 5;
        for(int i = 0, l = 1, r = 1, u = 1 ;   i < n ;   i++){
            point <DT> edge = (p[(i+1)%n]- p[i])/sqrt(DisSq(p[i], p[(i+1)%n]));

            for( ; (edge ^ p[r%n]-p[i]) < (edge ^ p[(r+1)%n] - p[i]); r++); 
            for( ; u<r || (edge & p[u%n] - p[i]) < (edge & p[(u+1)%n] - p[i]); u++) ;
            for( ; l<u || (edge ^ p[l%n] - p[i]) > (edge ^ p[(l+1)%n] - p[i]); l++);
            
            double w = (edge ^ p[r%n]-p[i]) - (edge ^ p[l%n] - p[i]);
            double h = UTriArea(p[u%n], p[i], p[(i+1)%n])/sqrt(DisSq(p[i], p[(i+1)%n]));
            area = min(area,w*h);
        }
        if(area>1e19) 
            area = 0;
        return area;
    }
    template <typename DT> DT FarthestPairOfPoints(polygon <DT> p){
        p = ConvexHull(p);
        int n = p.size();
        DT ans = -1e9;
        for(int i = 0, j = 1; i < n; i++)
        {   
            for( ; UTriArea(p[i], p[(i + 1) % n], p[(j + 1) % n]) > UTriArea(p[i], p[(i + 1) % n], p[j]) ; j = (j + 1) % n ) ;
            ans = max(ans, DisSq(p[i], p[j]));
            ans = max(ans, DisSq(p[(i + 1) % n], p[j]));
        }
        return ans; // will return square of the answer.
    }
    template <typename DT> int PointInConvexPolygon(polygon <int> :: iterator b, polygon <int> :: iterator e, const point <DT> &O){
        polygon <int> :: iterator lo = b + 2, hi = e - 1, ans = e;
        while(lo <= hi) {
            auto mid = lo + (hi - lo) / 2;
            if(TriArea(*b, O, *mid) >= 0) ans = mid, hi = mid - 1;
            else lo = mid + 1;
        }
        if (ans == e or abs(UTriArea(*b, *(ans - 1), *ans) - UTriArea(*b, *(ans - 1), O) - UTriArea(*b, *ans, O) - UTriArea(*(ans - 1), *ans, O)) > EPS)
            return 0;
        else return (Collinear(*b, *(b + 1), O) or Collinear(*(e - 1), *b, O) or Collinear(*(ans), *(ans - 1), O)) ? -1 : 1;
    } // 0 for outside, -1 for on border, 1 for inside

    template <typename DT> int PointInPolygon(polygon <DT> &P, point <DT> pt) {
        int n = P.size();
        int cnt = 0;
        for(int i = 0, j = 1; i < n; i++, j = (j + 1) % n) {
            if(TriArea(pt, P[i], P[j]) == 0 and min(P[i], P[j]) <= pt and pt <= max(P[i], P[j]))
                return -1;
            cnt += ((P[j].y >= pt.y) - (P[i].y >= pt.y)) * TriArea(pt, P[i], P[j]) > 0; 
        }
        return cnt & 1;
    }
}
using namespace polygon_algo;
/*....................................................................*/ 

void solve() {
    circle <double> C;
    polygon <double> P(4);
    double ans = 0;
    cin >> C.O >> C.R >> P[1] >> P[3];
    P[0] = {min(P[3].x, P[1].x), min(P[3].y, P[1].y)};
    P[2] = {max(P[3].x, P[1].x), max(P[3].y, P[1].y)};
    P[1] = {P[2].x, P[0].y}, P[3] = {P[0].x, P[2].y};
    for(int i = 0; i < 4; i++){
        ans += C.SegmentedArea(P[i], P[(i + 1) % 4]);
    }
    cout << fixed << setprecision(8) << ans << '\n';
}

int main()
{
    monke_flip
    int t = 1; 
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cout << "Case " << tc << ": ";
        solve();
    }
    return MONKE;
}