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

const int maxn = (1<<20)+5 ;
int logs[maxn] = {0};

void compute_logs(){
	logs[1] = 0;
	for(int i=2;i<(1<<20);i++){
		logs[i] = logs[i/2]+1;
	}
}

class Sparse_Table
{
	public:
		vector <vector<ll>> table; 
		function < ll(ll,ll) > func;
		ll identity;

	Sparse_Table(vector <ll> &v, function <ll(ll,ll)> _func, ll id){
		if(logs[2] != 2) compute_logs();
		int sz = v.size();
		table.assign(sz,vector <ll>(logs[sz]+1) );
		func = _func, identity = id;

		for(int j=0;j<=logs[sz];j++){
			for(int i=0;i+(1<<j)<=sz;i++){
				if(j==0) table[i][j] = func(v[i],id);	// base case, when only 1 element in range
				else table[i][j] = func(table[i][j-1], table[i + (1<<(j-1))][j-1] );
			}
		}
	}
	// when intersection of two ranges wont be a problem like min, gcd,max
	ll query(int l, int r){
		assert(r>=l);
		int pow = logs[r-l+1];
		return func(table[l][pow], table[r- (1<<pow) + 1][pow]);
	}
	// other cases like sum
	ll Query(int l,int r){
		if(l>r) return identity; // handle basecase
		int pow = logs[r - l + 1];
		return func(table[l][pow], Query(l+(1<<pow), r));
	}
};

void solve(){
	int n,m;
	cin>>n>>m;
	string s;
	cin>>s;
	vector <ll> arr(n+1);
	for(int i=0;i<n;i++){
		if(s[i]=='+') arr[i+1] = arr[i] + 1;
		else arr[i+1] = arr[i] - 1;
	}
	Sparse_Table MIN(arr, [](ll a,ll b){return min(a,b);}, LLONG_MAX);
	Sparse_Table MAX(arr, [](ll a,ll b){return max(a,b);}, LLONG_MIN);
	while(m--){
		int l,r;
		cin>>l>>r;
		ll mn = MIN.query(0,l-1);
		ll mx = MAX.query(0,l-1);
		if(n>r) {
			mn = min(mn,arr[l-1]-arr[r]+MIN.query(r+1,n));
			mx = max(mx,arr[l-1]-arr[r]+MAX.query(r+1,n));
		}
		cout<<mx-mn+1<<endl;
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