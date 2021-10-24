// Cirumference of an Elipse
#include <bits/stdc++.h>
using namespace std;
double a,b;
const double SIMPSON_TERMINAL_EPS = 1e-12;
complex <double> F(double x){
	return x;
}
template <typename DT> DT simpson(const function <DT(double)>& F,double minx, double maxx){
    return (maxx - minx) / 6 * (F(minx) + 4 * F((minx + maxx) / 2.) + F(maxx));
}

template <typename DT> DT adaptive_simpson(const function <DT(double)>& F, double minx, double maxx, double c, double EPS){
    if(maxx - minx < SIMPSON_TERMINAL_EPS) return 0;
    double midx = (minx + maxx) / 2;
    double a = simpson(F, minx, midx);
    double b = simpson(F, midx, maxx);

    if(fabs(a+b-c)<15*EPS) return a+b+(a+b-c)/15.0;

    return adaptive_simpson(F,minx,midx,a,EPS/2.)+adaptive_simpson(F,midx,maxx,b,EPS/2.);
}
template <typename DT> DT adaptive_simpson(const function <DT(double)>& F, double minx, double maxx, double EPS){
    return adaptive_simpson(F, minx, maxx, simpson(F, minx, maxx), EPS);
}

int main()
{
	function <complex <double> (double)> G = F;
	auto ans = adaptive_simpson(G, 0, 6 ,1e-12);
	cout << ans <<  '\n';
	return 0;
}
