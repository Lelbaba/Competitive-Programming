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

void solve(){
    pair< point <int>,point <int> > P,Q;
    P.first.scan(); P.second.scan(); Q.first.scan(); Q.second.scan();
    point <int> lo(max(P.first.x,Q.first.x),max(P.first.y,Q.first.y));
    point <int> hi(min(P.second.x,Q.second.x),min(P.second.y,Q.second.y));
    if(hi.x>lo.x and hi.y> lo.y)
        cout<<lo.x<<" "<<lo.y<<" "<<hi.x<<" "<<hi.y<<'\n';
    else 
        cout<<"No Overlap\n";
}

int main()
{
    monke_flip
    int t = 1; 
    cin>>t;
    for(int tc=1; tc<=t; tc++){
        if(tc>1) 
            cout<<'\n';
        solve();
    }
    return MONKE;
}