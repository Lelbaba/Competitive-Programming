#include <bits/stdc++.h>
using namespace std;
// ONLY SQUARE MATRIX
const long long mod = 1e9+7;
class Matrix
{
	public:
		vector <vector <long long> > data;
		int size;
	Matrix(int sz){
		size = sz;
		data.resize(sz, vector <long long> (sz,0) ); 
	};
	void operator *= (Matrix rhs){
		assert(size == rhs.size);

		Matrix lhs(size);
		lhs.data = data;
		int r,c,x;
		
		for(r=0; r<size; r++) for(c=0; c<size; c++){
			data[r][c] = 0;
			for(x=0; x<size; x++){
				data[r][c] = (data[r][c] + (lhs.data[r][x]*rhs.data[x][c])%mod )%mod;
			}
		}
	}

	void make_unit(){
		for(int i=0; i<size; i++) for(int j=0; j<size; j++) data[i][j] = (i==j);
	}
};

void exp(Matrix& base, int pow){
	Matrix ans(base.size);
	ans.data = base.data;
	base.make_unit();
	while(pow) {
		if(pow&1) base*=ans;
		ans*=ans;
		pow >>= 1;
	}
}

int main()
{
	int tc,t,k,n;
	cin>>tc;

	while(tc--) {
		cin >> t >> k >> n;
		Matrix sol(t+1);
		sol.data[0][0] = k+1;
		sol.data[0][t] = -k;
		for(int i=1;i<=t;i++) sol.data[i][i-1] = 1;

		exp(sol,n);
		Matrix vec(t+1); vec.data[t][0] = 1;
		for(int i=t-1; i>=0; i--)	vec.data[i][0] = (vec.data[i+1][0]*(k+1))%mod;
		vec.data[0][0]-=1;

	
		sol*=vec;
		cout<<(sol.data[t][0]+mod)%mod<<endl;
	}
	return 0;
}