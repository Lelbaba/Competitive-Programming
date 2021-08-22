#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using LL = long long;
const int MONKE = 0;

const int maxn = (1<<20)+5 ;
int logs[maxn] = {0};

void compute_logs(){
	// can also use log(x) = 31 - __builtin_clz(x)
	logs[1] = 0;
	for(int i=2;i<(1<<20);i++){
		logs[i] = logs[i/2]+1;
	}
}

class Sparse_Table
{
	public:
		vector <vector<LL>> table; 
		function < LL(LL,LL) > func;
		LL identity;

	Sparse_Table(vector <LL> &v, function <LL(LL,LL)> _func, LL id){
		if(logs[2] != 1) compute_logs();
		int sz = v.size();
		table.assign(sz,vector <LL>(logs[sz]+1) );
		func = _func, identity = id;

		for(int j=0;j<=logs[sz];j++){
			for(int i=0;i+(1<<j)<=sz;i++){
				if(j==0) table[i][j] = func(v[i],id);	// base case, when only 1 element in range
				else table[i][j] = func(table[i][j-1], table[i + (1<<(j-1))][j-1] );
			}
		}
	}
	// when intersection of two ranges wont be a problem like min, gcd,max
	LL query(int l, int r){
		assert(r>=l);
		int pow = logs[r-l+1];
		return func(table[l][pow], table[r- (1<<pow) + 1][pow]);
	}
	// other cases like sum
	LL Query(int l,int r){
		if(l>r) return identity; 
		int pow = logs[r - l + 1];
		return func(table[l][pow], Query(l+(1<<pow), r));
	}
};

void solve(){
	int n,m;
	cin>>n>>m;
	string s;
	cin>>s;
	vector <LL> arr(n+1);
	for(int i=0;i<n;i++){
		if(s[i]=='+') arr[i+1] = arr[i] + 1;
		else arr[i+1] = arr[i] - 1;
	}
	Sparse_Table MIN(arr, [](LL a,LL b){return min(a,b);}, LLONG_MAX);
	Sparse_Table MAX(arr, [](LL a,LL b){return max(a,b);}, LLONG_MIN);
	while(m--){
		int l,r;
		cin>>l>>r;
		LL mn = MIN.query(0,l-1);
		LL mx = MAX.query(0,l-1);
		if(n>r) {
			mn = min(mn,arr[l-1]-arr[r]+MIN.query(r+1,n));
			mx = max(mx,arr[l-1]-arr[r]+MAX.query(r+1,n));
		}
		cout<<mx-mn+1<<'\n';
	}
}

int main()
{
	monke_flip
	int t = 1; 
	cin>>t;
	for(int tc=1; tc<=t; tc++){
		solve();
	}
	return MONKE;
}