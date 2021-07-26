#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif
#define print(x) cout << #x << ":\n";
using namespace std;
using ll = long long;
const int MONKE = 0;

class modulo_int{
    public:
        ll val;
        static const ll mod = 1e9+7;

    modulo_int(ll _val = 0){
        val = _val > 0 ? _val%mod : _val%mod + mod;
    }

    ll inv_mod(ll a, ll m){
        ll _m = m, q, t, x, y;
        if (m == 1) return 0;
        for (y = 0, x = 1; a>1; y = x-q*y, x = t) {
            q = a/m, t = m;
            m = a%m, a = t;
            t = y;
        }
        return x < 0 ? x+_m: x;
    }
    modulo_int operator + (modulo_int rhs){ return modulo_int((val + rhs.val)); }
    modulo_int operator - (modulo_int rhs){ return modulo_int((val - rhs.val)); }
    modulo_int operator * (modulo_int rhs){ return modulo_int((val*rhs.val)); }
    modulo_int operator / (modulo_int rhs){ return modulo_int((val*inv_mod(rhs.val, mod)));}

    void operator += (modulo_int rhs){ *this = *this + rhs; }
    void operator -= (modulo_int rhs){ *this = *this - rhs; }
    void operator *= (modulo_int rhs){ *this = *this * rhs; }
    void operator /= (modulo_int rhs){ *this = *this / rhs; }
    friend modulo_int binpow (modulo_int val, ll p){
        modulo_int ans = 1;
        for(;p>0; p>>=1){
            if(p&1) ans = ans*val;
            val *= val;
        }
        return ans;
    }
    friend ostream& operator << (ostream& o, modulo_int &a){
        o << a.val;
        return o;
    }
    friend istream& operator >> (istream& o, modulo_int &a){
        o >> a.val;
        return o;
    }
};
template <typename TYPE>
class Matrix {
    public:
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
    void operator += (Matrix& R){
        assert(n == R.n and m == R.m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                dt[i][j] += R.dt[i][j];
    }
    void operator -= (Matrix &R){
        assert(n == R.n and m == R.m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                dt[i][j] -= R.dt[i][j];
    }
    void operator *= (TYPE R){
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                dt[i][j]*= R;
    }
    void operator /= (TYPE R){
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                dt[i][j]/= R;        
    }
    Matrix operator + (Matrix& R){
        Matrix ans = *this;
        ans += R;
        return ans;
    }
    Matrix operator - (Matrix& R){
        Matrix ans = *this;
        ans -= R;
        return ans;
    }
    Matrix operator * (TYPE R){
        Matrix ans = *this;
        ans *= R;
        return ans;
    }
    Matrix operator / (TYPE R){
        Matrix ans = *this;
        ans /= R;
        return ans;
    }
    Matrix operator * (Matrix& R){
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
    Matrix operator ~ (){
        Matrix ans(m,n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                ans.dt[j][i] = dt[i][j];
        return ans;
    }
    void unit(){
        assert(n == m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                dt[i][j] = (i == j);
    }

    vector <TYPE> apply(vector <TYPE> V){
        Matrix A(V);
        A = (~A);
        A = *this*A;
        A = ~(A);
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
    friend ostream& operator << (ostream& o, Matrix& M){
        for(auto &x: M.dt){
            for(auto &y: x)
                cout << y << ' ';
            cout << '\n';
        }
        return o;
    }
};
int main()
{
    monke_flip
    Matrix <modulo_int> A({{1,1},{1,0}});
    A = binpow(A, 100);
    auto z = A.apply({1,1});
    for(auto x:z)
        cout << x << ' ';
    return MONKE;
}