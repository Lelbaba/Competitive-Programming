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
using LL = long long;
const int MONKE = 0;

struct modulo_int {
    LL val;
    static const LL mod = 1e9 + 7; /* don't use if it isn't a prime, careful of overflow*/

    modulo_int(LL _val = 0) {
        val = _val > 0 ? _val % mod : _val % mod + mod;
    }

    modulo_int operator + (modulo_int rhs) { return modulo_int((val + rhs.val)); }
    modulo_int operator - (modulo_int rhs) { return modulo_int((val - rhs.val)); }
    modulo_int operator * (modulo_int rhs) { return modulo_int((val * rhs.val)); }
    modulo_int operator / (modulo_int rhs) { return modulo_int( binpow(rhs, mod - 2) * val);}

    void operator += (modulo_int rhs) { *this = *this + rhs; }
    void operator -= (modulo_int rhs) { *this = *this - rhs; }
    void operator *= (modulo_int rhs) { *this = *this * rhs; }
    void operator /= (modulo_int rhs) { *this = *this / rhs; }

    friend modulo_int binpow (modulo_int val, LL p) {
        modulo_int ans = 1;
        for (; p > 0; p >>= 1) {
            if (p & 1) ans = ans * val;
            val *= val;
        }
        return ans;
    }
    friend ostream& operator << (ostream& o, modulo_int &a) {
        o << a.val;
        return o;
    }
    friend istream& operator >> (istream& o, modulo_int &a) {
        o >> a.val;
        return o;
    }
    friend LL abs(modulo_int a) {
        return abs(a.val);
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
    void append_column(vector <TYPE> v){
        assert(v.size() == n);
        m++;
        for(int i = 0; i < n; i++)
            dt[i].push_back(v[i]);
    }
    void append_row(vector <TYPE> v){
        assert(v.size() == m);
        n++, dt.push_back(v);
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