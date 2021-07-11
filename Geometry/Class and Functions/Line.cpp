#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MONKE = 0;
const double eps = 1e-9;
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