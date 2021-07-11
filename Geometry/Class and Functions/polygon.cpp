template <typename DT> 
class polygon{
    public:
        vector <point<DT>> points;
    polygon( vector<point<DT>> &pt){
        points = pt;
    }
    polygon <DT> Convex_Hull(){
        auto PT = points;
        sort(PT.begin(),PT.end());
        int m=0, n=PT.size();
        vector <point <DT>> hull(n+n+2);
        for(int i=0;i<n;i++){ 
            while(m>1 && (hull[m-2].tri_area(hull[m-1],PT[i]))<=0 ) m--;
            hull[m++] = PT[i];
        }
        int k=m;
        for(int i=n-2;i>=0;i--){
            while(m>k && (hull[m-2].tri_area(hull[m-1],PT[i]))<=0) m--;
            hull[m++] = PT[i];
        }
        if(n>1) m--;
        while(hull.size()>m) hull.pop_back();
        return polygon(hull);
    }
};