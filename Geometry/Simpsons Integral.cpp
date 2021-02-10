#include <bits/stdc++.h>
using namespace std;

double a,b;
const int N = 10000;
double f(double x){
	return sqrt(a*a*cos(x)*cos(x) + b*b*sin(x)*sin(x));
}
double simpson_integration(double a, double b){
    double h = (b - a) / N;
    double s = f(a) + f(b); // a = x_0 and b = x_2n
    for (int i = 1; i <= N - 1; ++i) { // Refer to final Simpson's formula
        double x = a + h * i;
        s += f(x) * ((i & 1) ? 4 : 2);
    }
    s *= h / 3;
    return s;
}


int main()
{
	int n;
	scanf("%d", &n);
	for(int i=0;i<n;i++){
		scanf("%lf %lf", &a,&b);
		double ans = 4*simpson_integration(0,asin(1));
		printf("Case %d: %.6lf\n",i+1, ans);
	}
	return 0;
}
