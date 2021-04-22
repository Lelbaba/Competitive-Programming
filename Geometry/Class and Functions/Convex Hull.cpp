#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MONKE = 0;
using pt = point <double>;
vector <pt> Convex_Hull(vector <pt> &points){

    sort(points.begin(),points.end());
    int m=0, n=points.size();
    vector <pt> hull(n+n+2);
    for(int i=0;i<n;i++){ 
        while(m>1 && (hull[m-2].tri_area(hull[m-1],points[i]))<=0 ) m--;
        hull[m++] = points[i];
    }
    int k=m;
    for(int i=n-2;i>=0;i--){
        while(m>k && (hull[m-2].tri_area(hull[m-1],points[i]))<=0) m--;
        hull[m++] = points[i];
    }
    if(n>1) m--;
    while(hull.size()>m) hull.pop_back();
    return hull;
}
int main()
{
    return MONKE;
}