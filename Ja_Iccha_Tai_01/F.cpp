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
using ld = long double;

ll C[55][55];

void init(){
	int n = 50;
	for(int i=0; i<=n; i++){
		for(int j=0; j<=i; j++){
			if(j==0 or j==i )
				C[i][j] = 1;
			else
				C[i][j] = C[i-1][j-1] + C[i-1][j];
		}
	}
}

void solve(){
	int n;
	ld p;
	cin >>n >>p;
	ld inv = 1 - p, ans = 0;
	ld P = pow(p,2*n-1), INV = 1;
	
	if(p>0.00+1e-8){
		for(int i=0; i<n; i++, P/=p, INV*=inv){
			ans += C[2*n-1][i]*P*INV;
		}
	}
	cout<<fixed<<setprecision(2)<<ans<<'\n';
}

int main()
{
	monke_flip
	int t = 1;
	init(); 
	cin>>t;
	for(int tc=1; tc<=t; tc++){
		solve();
	}
	return MONKE;
}