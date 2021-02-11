#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 2; // it doesn't actually have to be infinity or a big number
const ll mod = 998244353;
int D[][2] = {
	{1,0},
	{-1,0},
	{0,1},
	{0,-1}
};
ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
ll inv(ll n){
	ll x,y;
	ll g = gcd(n,mod,x,y);
	return ((x%mod+mod)%mod);
}

int modular_gauss (vector < vector<ll> > a, vector<ll> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (a[sel][col] == 0)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                ll c = ((a[i][col] *inv(a[row][col]))%mod + mod)%mod;
                for (int j=col; j<=m; ++j)
                    a[i][j] = ((a[i][j] - (a[row][j] * c)%mod)%mod +mod)%mod;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = ((a[where[i]][m] * inv(a[where[i]][i])%mod)+mod)%mod;
    for (int i=0; i<n; ++i) {
        ll sum = 0;
        for (int j=0; j<m; ++j)
            sum = (sum+(ans[j] * a[i][j])%mod+mod)%mod;
        if (sum != a[i][m])
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}
int mat[30][30];

vector <vector <ll> > parse_input(int &n,int &m){
	int i,j,k;
	cin>>n>>m;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			cin>>mat[i][j];
		}
	}
	vector <vector <ll> > v(n*m,vector <ll> (n*m+1,0));
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			int key = i*m+j;
			int cnt = 0;

			if(mat[i][j]>1) for( k=0; k<4; k++){
				int I = i+D[k][0],J = j+D[k][1];
				if(I<0||I>=n||J<0||J>=m) continue;
				int adj_key = I*m+J;
				v[key][adj_key] = -1;
				cnt++;
			}

			v[key][key] = max(1,cnt);
			v[key][n*m] = cnt;
		}
	}
	return v;
}

void query(vector <ll> &ans,int m){
	int q,i,j;
	cin>>q;
	while(q--){
		cin>>i>>j;
		i--;j--;
		cout<<ans[i*m+j]<<endl;
	}
}

int main()
{
	int t,n,m,q,i,j;
	cin>>t;
	while(t--){
		vector <ll> ans;
		modular_gauss(parse_input(n,m),ans);
		query(ans,m);
	}
	return 0;
}
