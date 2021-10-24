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

template <LL mod> struct INT_MOD {
    LL val;
    INT_MOD(LL _val = 0) {
        val = _val > 0 ? _val % mod : _val % mod + mod;
    }

    INT_MOD operator + (INT_MOD rhs) const { return INT_MOD((val + rhs.val)); }
    INT_MOD operator - (INT_MOD rhs) const { return INT_MOD((val - rhs.val)); }
    INT_MOD operator * (INT_MOD rhs) const { return INT_MOD((val * rhs.val)); }
    INT_MOD operator / (INT_MOD rhs) const { return INT_MOD( binpow(rhs, mod - 2) * val);}

    void operator += (INT_MOD rhs) { *this = *this + rhs; }
    void operator -= (INT_MOD rhs) { *this = *this - rhs; }
    void operator *= (INT_MOD rhs) { *this = *this * rhs; }
    void operator /= (INT_MOD rhs) { *this = *this / rhs; }

    friend INT_MOD binpow (INT_MOD val, LL p) {
        INT_MOD ans = 1;
        for (; p > 0; p >>= 1) {
            if (p & 1) ans = ans * val;
            val *= val;
        }
        return ans;
    }
    friend ostream& operator << (ostream& o, INT_MOD &a) {
        o << a.val;
        return o;
    }
    friend istream& operator >> (istream& o, INT_MOD &a) {
        o >> a.val;
        return o;
    }
    friend LL abs(INT_MOD a) {
        return abs(a.val);
    }
};
template <typename TYPE>
class Matrix {
    public:
        int n, m;
        vector <vector <TYPE>> dt;
    Matrix(int n = 1, int m = 1): n(n), m(m), dt(n, vector <TYPE>(m)) {}
    Matrix(const vector <vector <TYPE>>& dt): n(dt.size()), m(dt[0].size()), dt(dt) {}
    Matrix(const vector <TYPE>& dt) : n(1), m(dt.size()), dt({dt}) {}

    vector <TYPE>& operator[] (int idx){
        return dt[idx];
    }
    template <typename D> void operator = (const vector <vector <D>> &v){
        assert(!v.empty());
        n = v.size(), m = v[0].size();
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                dt[i][j] = TYPE(v[i][j]);
    }
    void operator += (const Matrix& R){
        assert(n == R.n and m == R.m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                dt[i][j] += R.dt[i][j];
    }
    void operator -= (const Matrix& R){
        assert(n == R.n and m == R.m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                dt[i][j] -= R.dt[i][j];
    }
    void operator *= (const TYPE& R){
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                dt[i][j]*= R;
    }
    void operator /= (const TYPE& R){
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                dt[i][j]/= R;        
    }
    Matrix operator + (const Matrix& R) const {
        Matrix ans = *this;
        ans += R;
        return ans;
    }
    Matrix operator - (const Matrix& R) const {
        Matrix ans = *this;
        ans -= R;
        return ans;
    }
    Matrix operator * (const TYPE& R) const {
        Matrix ans = *this;
        ans *= R;
        return ans;
    }
    Matrix operator / (const TYPE& R) const {
        Matrix ans = *this;
        ans /= R;
        return ans;
    }
    Matrix operator * (const Matrix& R){
        assert(m == R.n);
        Matrix ans (n, R.m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < R.m; j++)
                for (int k = 0; k < m; k++)
                    ans[i][j] += dt[i][k] * R.dt[k][j];
        return ans;
    } 
    void operator *= (const Matrix &R){
        *this = *this * R;
    }
    Matrix get_transpose(){
        Matrix ans(m,n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                ans.dt[j][i] = dt[i][j];
        return ans;
    }
    void make_unit(){
        assert(n == m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                dt[i][j] = (i == j);
    }

    vector <TYPE> apply(const vector <TYPE>& V){
        Matrix A(V);
        return (*this * A.get_transpose()).get_transpose()[0];
    }
    void append_column(vector <TYPE> v){
        assert(v.size() == n);
        m++;
        for(int i = 0; i < n; i++)
            dt[i].push_back(v[i]);
    }
    void append_row(const vector <TYPE>& v){
        assert(v.size() == m);
        n++, dt.push_back(v);
    }
    friend Matrix binpow(Matrix R, long long pow){
        Matrix ans(R.n, R.m);
        ans.make_unit();
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
using modulo_int = INT_MOD <1000000007>;
int main()
{
    monke_flip
    Matrix <modulo_int> A({{1,1},{1,0}});
    A = binpow(A, 4);
    auto z = A.apply({1,1});
    for(auto x:z)
        cout << x << ' ';
    return MONKE;
}