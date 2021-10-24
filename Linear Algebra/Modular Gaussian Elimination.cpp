//This code is untested

#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const LL mod = 998244353;
int D[][2] = {
	{1,0},
	{-1,0},
	{0,1},
	{0,-1}
};
struct modulo_int{
    LL val;
    static const LL mod = 998244353; // don't use if it isn't a prime, careful of overflow
    modulo_int(LL _val = 0){
        val = _val > 0 ? _val%mod : _val%mod + mod;
    }
    modulo_int operator + (modulo_int rhs){ return modulo_int((val + rhs.val)); }
    modulo_int operator - (modulo_int rhs){ return modulo_int((val - rhs.val)); }
    modulo_int operator * (modulo_int rhs){ return modulo_int((val * rhs.val)); }
    modulo_int operator / (modulo_int rhs){ return modulo_int( binpow(rhs, mod-2) * val);}

    void operator += (modulo_int rhs){ *this = *this + rhs; }
    void operator -= (modulo_int rhs){ *this = *this - rhs; }
    void operator *= (modulo_int rhs){ *this = *this * rhs; }
    void operator /= (modulo_int rhs){ *this = *this / rhs; }
    friend modulo_int binpow (modulo_int val, LL p){
        modulo_int ans = 1;
        for(;p>0; p>>=1){
            if(p&1) ans = ans*val;
            val *= val;
        }
        return ans;
    }
};
template <typename TYPE> struct Matrix {
    int n, m;
    vector <vector <TYPE>> dt;
    Matrix(int n = 1, int m = 1): n(n), m(m) {
        dt.assign(n, vector <TYPE> (m));
    };
    Matrix(vector <vector <TYPE>> dt): n(dt.size()), m(dt[0].size()), dt(dt) {};
    vector <TYPE>& operator[] (int idx){
        return dt[idx];
    }
    Matrix(vector <TYPE> d): n(1), m(d.size()), dt({d}) {};
    template <typename D> void operator = (vector <vector <D>> v){
        assert(!v.empty());
        n = v.size(), m = v[0].size();
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                dt[i][j] = TYPE(v[i][j]);
    }
    Matrix operator * (Matrix& R){ //Matrix multiplication
        assert(m == R.n);
        Matrix ans (n, R.m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < R.m; j++)
                for (int k = 0; k < m; k++)
                    ans[i][j] += dt[i][k] * R.dt[k][j];
        return ans;
    } 
    void operator *= (Matrix &R){
        *this = *this * R;
    }
    // Matrix Transpose
    Matrix operator ~ (){
        Matrix ans(m,n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                ans.dt[j][i] = dt[i][j];
        return ans;
    }
    // makes the matrix unit
    void unit(){
        assert(n == m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                dt[i][j] = (i == j);
    }
    //applies linear transformation on a vector
    vector <TYPE> apply(vector <TYPE> V){
        Matrix A(V);
        A = (~A);
        A = ~(*this*A);
        return A[0];
    }
    friend Matrix binpow(Matrix R, long long pow){
        assert(R.n == R.m);
        Matrix ans(R.n, R.n);
        ans.unit();
        for( ; pow > 0; pow >>= 1, R*= R){
            if(pow & 1)
                ans *= R;
        }
        return ans;
    }
};
const double EPS = 1e-9;
const int INF = 2; // it doesn't actuaLLy have to be infinity or a big number

LL abs(modulo_int a){
	return abs(a.val);
}
template <typename T> 
class gauss {
    vector <vector <T>> a;
    vector <T> ans;
public:
    void add(vector <T> &coef, T cnst){
        a.push_back(coef);
        a.back().push_back(cnst);
    }
    int gauss () {
        int n = (int) a.size();
        int m = (int) a[0].size() - 1;

        vector<int> where (m, -1);
        for (int col=0, row=0; col<m && row<n; ++col) {
            int sel = row;
            for (int i=row; i<n; ++i)
                if (abs (a[i][col]) > abs (a[sel][col]))
                    sel = i;
            if (abs (a[sel][col]) < EPS)
                continue;
            for (int i=col; i<=m; ++i)
                swap (a[sel][i], a[row][i]);
            where[col] = row;

            for (int i=0; i<n; ++i)
                if (i != row) {
                    double c = a[i][col] / a[row][col];
                    for (int j=col; j<=m; ++j)
                        a[i][j] -= a[row][j] * c;
                }
            ++row;
        }

        ans.assign (m, 0);
        for (int i=0; i<m; ++i)
            if (where[i] != -1)
                ans[i] = a[where[i]][m] / a[where[i]][i];
        for (int i=0; i<n; ++i) {
            dt sum = 0;
            for (int j=0; j<m; ++j)
                sum += ans[j] * a[i][j];
            if (abs (sum - a[i][m]) > EPS)
                return 0;
        }

        for (int i=0; i<m; ++i)
            if (where[i] == -1)
                return INF;
        return 1;
    }
    vector <T>& get_ans(){
        return ans;
    }
}


int main()
{
	int t,n,m,q,i,j;
	cin>>t;
	while(t--){
		vector <LL> ans;
		modular_gauss(parse_input(n,m),ans);
		query(ans,m);
	}
	return 0;
}
