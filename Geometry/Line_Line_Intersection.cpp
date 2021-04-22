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
using ld = long double;
const int MONKE = 0;
const double eps = 1e-9;

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

template <typename DT>
class line{
    public:
        point <DT> dir, O; // direction of vector and starting point
    line(point <DT> p,point <DT> q){
        dir = q-p;
        O = p;
    }
    bool parallel(line &L){
        return fabs(dir.cross(L.dir)) < eps;
    }
    bool collinear(point <DT> &p){
        point <DT> tem = p - O;
        return fabs(dir.cross(tem)) < eps;
    }
    int intersection(line L, point <double> &p){
        if(parallel(L)){
            if(collinear(L.O)) return -1;
            return 0;
        }
        point <DT> R = L.O - O;
        double t = double(R.cross(L.dir))/dir.cross(L.dir);
        point <double> ans(O.x,O.y), DIR(dir.x,dir.y);
        p = ans + (DIR*t);
        return 1;
    }
    line perp(point <DT> p){
        point <DT> tem(-dir.y,dir.x);
        return line(p,p+tem);
    }
};
void solve(){
    point <int> a,b,c,d;
    a.scan();
    b.scan();
    c.scan();
    d.scan();
    point <double> ans;
    line <int> P(a,b),Q(c,d);
    int chk = P.intersection(Q,ans);
    if(chk == 0) cout<<"NONE\n";
    else if(chk == -1) cout<<"LINE\n";
    else{
        cout<<"POINT ";
        cout<<fixed<<setprecision(2)<<ans.x<<' '<<ans.y<<'\n';
    }
}

int main()
{
    monke_flip
    int t = 1; 
    cin>>t;
    cout<<"INTERSECTING LINES OUTPUT\n";
    for(int tc=1; tc<=t; tc++){
        solve();
    }
    cout<<"END OF OUTPUT\n";
    return MONKE;
}