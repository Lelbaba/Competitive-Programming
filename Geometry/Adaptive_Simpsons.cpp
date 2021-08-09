// Cirumference of an Elipse
#include <bits/stdc++.h>
using namespace std;
double a,b;
const double SIMPSON_TERMINAL_EPS = 1e-12;
double F(double x){
	return cos(x);
}
double simpson(double minx, double maxx){
    return (maxx - minx) / 6 * (F(minx) + 4 * F((minx + maxx) / 2.) + F(maxx));
}
double adaptive_simpson(double minx, double maxx, double c, double EPS){
    if(maxx - minx < SIMPSON_TERMINAL_EPS) return 0;
    double midx = (minx + maxx) / 2;
    double a = simpson(minx, midx);
    double b = simpson(midx, maxx);

    if(fabs(a+b-c)<15*EPS) return a+b+(a+b-c)/15.0;

    return adaptive_simpson(minx,midx,a,EPS/2.)+adaptive_simpson(midx,maxx,b,EPS/2.);
}
double adaptive_simpson(double minx, double maxx, double EPS){
    return adaptive_simpson(minx, maxx, simpson(minx, maxx), EPS);
}

int main()
{
	int n;
	scanf("%d", &n);
	for(int i=0;i<n;i++){
		scanf("%lf %lf", &a,&b);
		double ans = 4*adaptive_simpson(0,acos(-1),1e-12);
		printf("Case %d: %.6lf\n",i+1, ans);
	}
	return 0;
}
