#include <bits/stdc++.h>
using namespace std;

const double e = 2.718281828459;
const double pi = acos(-1);
using cd = complex <double> ;

void FFT(vector < cd > &P, bool inverse){
	int n = P.size();	
	if(n==1){
		return;
	}
	int f = 0;
	cd w = polar(1.00,2*pi/n),W = 1;
	if(inverse){
		w = 1.00/w;
	}
	vector < cd > p[2];
	for(auto x:P){
		p[f].push_back(x); f^=1;
	}
	FFT(p[0],inverse);
	FFT(p[1],inverse);

	for(int i=0;i<n/2;i++){
		P[i] = p[0][i] + W*p[1][i];
		P[i+n/2] = p[0][i] - W*p[1][i];
		W*=w;
		if(inverse){
			P[i]/=2;
			P[i+n/2]/=2;
		}
	}
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    FFT(fa, false);
    FFT(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    FFT(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

int main()
{
	vector <cd > V;
	V.push_back(1);
	V.push_back(9);
	V.push_back(3);
	V.push_back(1);
	V.push_back(3.5);
	V.push_back(2.8);
	V.push_back(3.6);
	V.push_back(0);
	FFT(V,0);
	FFT(V,1);
	for(auto x:V){
		cout<<x<<endl;
	}
	return 0;
}
